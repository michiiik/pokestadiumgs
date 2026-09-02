# Container PR gate

`.github/workflows/container-gate.yml` + `container/gate_pr.sh` replace a
human manually re-gating a container-produced match before it merges: every
PR under `disasm/src/**`, `disasm/include/**`, `container/**`, or
`tools/**` gets a status check that rebuilds the ROM from the PR's sources
inside the prebuilt `gs-decomp-agent:latest` image (see
`docs/CONTAINER_AGENT.md`) on a self-hosted runner on this Mac Mini, and
passes only if the checksum matches. See the trigger-note comment at the
top of the workflow for what it does and doesn't catch by branch name
alone.

This page covers: registering the runner, making the check required, and
running the gate by hand.

## 1. What the gate actually does

`container/gate_pr.sh <checkout-dir>`:

1. Runs `gs-decomp-agent:latest` (`--entrypoint bash`, `--platform
   linux/amd64`) with the checkout bind-mounted read-only at `/src`.
2. Inside the container, replaces `/work/disasm/src` and
   `/work/disasm/include` with the checkout's copies, and overlays (without
   deleting) the checkout's `disasm/linker_scripts` onto the image's --
   these are the only inputs a `make -C disasm rom` (non-extract) build
   reads from outside the image; see the comment block at the top of
   `gate_pr.sh` for the exact `disasm/Makefile` reasoning.
   `disasm/asm/`, `disasm/assets/`, and `linker_scripts/*/auto/` are
   splat-extract output, gitignored, absent from any git checkout, and are
   never touched -- they stay exactly as baked into the image.
3. Runs `make -C disasm COMPARE=1 -j2` -- the same command
   `tools/container_agent.py` itself uses -- which links and then runs
   `md5sum` / `md5sum -c` against the retail checksum.
4. Exits `0` only if the gate output contains the literal line
   `build/pokestadiumgs-us.z64: OK`; otherwise it prints the container's
   full build/compare log and exits nonzero.

`check_decomp_provenance.py` is deliberately **not** run as part of this
gate. It checks `git diff --staged` (a pre-commit-hook contract; see its
own docstring and `.githooks/pre-commit`), and this gate never stages or
commits anything inside the container, so there is no staged diff for it
to read. Its accepted-attempt history (`disasm/probe-stats/`) is also
deliberately gitignored/untracked -- durable only on whichever host
produced it, not part of a PR checkout or reproducible from the image --
so a container rebuild-and-compare gate has no trustworthy way to answer
that check's question anyway. Provenance stays a commit-time concern on
the source repo (the pre-commit hook, and human review), separate from
this build gate.

## 2. Register the self-hosted runner (one-time, per Mac Mini)

Repo: `michiiik/pokemonStadiumGSRecompPrivate` (private). Label used by the
workflow: `gs-decomp` (alongside GitHub's automatic `self-hosted`, `macOS`,
`ARM64` labels).

Prerequisites on this Mac Mini:

- The `docker` CLI on `PATH` for whichever user account will run the
  runner service (OrbStack's CLI shim is enough -- the runner just shells
  out to `docker run`/`docker build`).
- `gs-decomp-agent:latest` already built (`container/build.sh` from a
  checkout of this repo) -- the gate does not build it for you unless you
  pass `gate_pr.sh --rebuild-image` yourself.
- `gh` authenticated with an account that has admin rights on the repo
  (`gh auth status`), to mint the runner registration token below.

Steps (GitHub's own actions-runner package, macOS arm64 build):

```bash
# 1. Mint a short-lived registration token (valid ~1 hour).
REG_TOKEN=$(gh api -X POST \
  repos/michiiik/pokemonStadiumGSRecompPrivate/actions/runners/registration-token \
  --jq .token)

# 2. Download the latest runner release for macOS arm64.
mkdir -p ~/actions-runner && cd ~/actions-runner
RUNNER_VERSION=$(gh api repos/actions/runner/releases/latest --jq '.tag_name | ltrimstr("v")')
curl -o actions-runner-osx-arm64.tar.gz -L \
  "https://github.com/actions/runner/releases/download/v${RUNNER_VERSION}/actions-runner-osx-arm64-${RUNNER_VERSION}.tar.gz"
tar xzf actions-runner-osx-arm64.tar.gz

# 3. Configure it against this repo, with the gs-decomp label.
./config.sh \
  --url https://github.com/michiiik/pokemonStadiumGSRecompPrivate \
  --token "$REG_TOKEN" \
  --name gs-mac-mini \
  --labels gs-decomp \
  --work _work
# Accept the defaults for runner group / work folder unless you have a
# reason to change them.
```

### Run it as a service

Either of these works; pick one.

**A. The runner's own service installer** (simplest -- wraps a launchd
plist for you):

```bash
cd ~/actions-runner
sudo ./svc.sh install
sudo ./svc.sh start
# sudo ./svc.sh status   # check it's running
# sudo ./svc.sh stop     # stop it
```

**B. A manual launchd plist**, if you want it running as your own user
(not root) so it inherits your login-session `docker`/OrbStack context
without extra setup: put a `LaunchAgents/com.github.actions.runner.plist`
under `~/Library/LaunchAgents` that runs `~/actions-runner/run.sh`
(`ProgramArguments`), set `RunAtLoad`/`KeepAlive` true, then
`launchctl bootstrap gui/$(id -u) ~/Library/LaunchAgents/com.github.actions.runner.plist`.
Use this instead of `svc.sh install` if `sudo ./svc.sh` runs the listener
as root and Docker/OrbStack is only wired up for your login user.

Once running, the runner shows up under repo Settings -> Actions ->
Runners with labels `self-hosted, macOS, ARM64, gs-decomp` -- confirm
those labels appear before relying on the workflow (they're what
`runs-on: [self-hosted, macOS, ARM64, gs-decomp]` matches against).

To deregister later:

```bash
REG_TOKEN=$(gh api -X POST \
  repos/michiiik/pokemonStadiumGSRecompPrivate/actions/runners/remove-token \
  --jq .token)
cd ~/actions-runner && ./config.sh remove --token "$REG_TOKEN"
```

## 3. Make the check required on the integration branch

Once the workflow has run at least once (a required check must have a
known status-check context to select), make `Rebuild + compare ROM in
container` (the job name in `container-gate.yml`) required on the
integration branch, e.g. `master`:

```bash
gh api -X PUT \
  repos/michiiik/pokemonStadiumGSRecompPrivate/branches/master/protection/required_status_checks \
  -f strict=true \
  -f 'checks[][context]=Rebuild + compare ROM in container' \
  -f 'checks[][app_id]=-1'
```

`app_id=-1` matches any app reporting that context (equivalent to omitting
app scoping in the UI). If branch protection isn't set up at all yet, use
the full `PUT .../protection` endpoint instead (see `gh api
repos/{owner}/{repo}/branches/{branch}/protection --help` /
GitHub's branch-protection API docs) to set `required_status_checks`
alongside whatever other rules the integration branch needs -- the command
above only touches the required-checks sub-resource and leaves existing
protection settings alone.

## 4. Run the gate locally

Same script the workflow calls, against any checkout (a worktree, a clone,
whatever):

```bash
container/gate_pr.sh /abs/path/to/checkout
```

Exit code `0` and a trailing `gate_pr.sh: PASS -- build/pokestadiumgs-us.z64: OK (<N>s)`
line on success; nonzero and the container's full build/compare log on
failure. Pass `--rebuild-image` first if your change touches `container/`
or the `Dockerfile` and you want to gate against a freshly built image
rather than whatever `gs-decomp-agent:latest` currently is:

```bash
container/gate_pr.sh /abs/path/to/checkout --rebuild-image
```

Requires: Docker (OrbStack is fine) with `linux/amd64` support, and
`gs-decomp-agent:latest` already built unless you pass `--rebuild-image`.
