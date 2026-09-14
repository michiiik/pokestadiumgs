# Public pull-request gate

The public repository uses a root-layout ROM gate. It validates the proposed
pull-request merge tree by rebuilding the US ROM and requiring the exact
checksum acceptance line:

```text
build/pokestadiumgs-us.z64: OK
```

## Local baseline setup

Use a clean public checkout on the isolated Mac runner. Keep the retail ROM
outside Git and either place a local ignored copy at
`baseroms/us/baserom.z64` or provide it through the environment:

```bash
POKESTADIUMGS_BASEROM=/private/path/baserom.z64 ci/build-baseline.sh
```

The resulting image is local-only:

```text
gs-decomp-agent-pokestadiumgs:latest
```

## Gate behavior

`ci/gate-pr.sh <checkout>` mounts the checkout read-only into a disposable
`linux/amd64` container on the Apple Silicon runner. The container has no
network, no Docker socket, and no repository write access. It overlays the
PR's tracked `src`, `include`, `tools`, `lib`, `linker_scripts`, `yamls`, and
`Makefile`, then runs the complete root build and checksum comparison.

The image must be rebuilt when the Python requirements or baseline build
inputs change. A YAML change is re-extracted inside the disposable gate
container.

## Contributor approval

The workflow uses `pull_request`, read-only contents permission, and no
secrets. Configure the public repository's Actions setting to **Require
approval for all external contributors**. Owners and collaborators can then
run automatically; external fork pull requests remain awaiting maintainer
approval until the proposed workflow and code have been reviewed.

For an external PR that needs a maintainer-triggered run, use
**Actions → Public PR ROM Gate → Run workflow** on `master` and provide its PR
number. The workflow checks GitHub's `refs/pull/<number>/merge` ref. Leave the
PR number empty to validate a same-repository branch or SHA instead.

Do not use a skipped trust-conditional job as the required check: GitHub treats
skipped conditional jobs as successful. Require the unique
`Public PR ROM Gate / Validate ROM against master` check only after the
workflow has produced its first successful result.

## Coverage and merging

`ci/update_coverage.py` renders the root-layout coverage snapshot from tracked
`src/` pragmas without needing the ROM. The PR workflow publishes the proposed
snapshot as an artifact.

`pr-integration.yml` implements the trusted same-repository path:

1. After a successful ROM gate, it verifies that the PR head and base SHAs have
   not changed and that the author is an owner, member, or collaborator.
2. On a GitHub-hosted runner, it runs the coverage generator from the exact
   trusted base revision against the PR merge tree.
3. If needed, it commits only the generated `COVERAGE.md` to the PR branch.
   That new commit starts a fresh ROM gate.
4. Once the second gate is successful and coverage is current, it enables
   squash auto-merge.

PRs that change `.github/`, `ci/`, `.dockerignore`, or `CODEOWNERS` are
deliberately excluded from automatic integration and require a maintainer-led
review and merge.

The integration workflow needs a GitHub App installed only on this repository,
with repository metadata read, contents write, and pull requests write. Store
its client ID as `PUBLIC_CI_APP_ID` and private key as
`PUBLIC_CI_APP_PRIVATE_KEY`. An App/PAT token is intentional: commits made
with the default `GITHUB_TOKEN` do not start another workflow, so the coverage
commit would otherwise bypass the second gate.

Automatic merging is feature-flagged off by default. Set the repository
variable `PUBLIC_CI_AUTOMERGE_ENABLED` to `true` only after `master` has a
required ROM-gate check and review protection, and GitHub's **Allow auto-merge**
setting is enabled.

Fork and non-verified PRs never receive the App token and remain maintainer
controlled. Their gate can be approved or manually dispatched, followed by a
manual coverage update and merge. The self-hosted gate must never receive
write permissions while running PR-controlled code.

## Phase 4 activation checklist

The live repository is not activated by this local change. Perform these steps
in order after publishing a reviewed commit containing both workflows:

1. Create and install the repository-scoped GitHub App, then configure
   `PUBLIC_CI_APP_ID` and `PUBLIC_CI_APP_PRIVATE_KEY`.
2. Require approval for all external contributors and enable GitHub auto-merge.
3. Protect `master`: require one approving review, stale-review dismissal,
   CODEOWNER review, up-to-date branches, and the exact check
   `Public PR ROM Gate / Validate ROM against master`.
4. Set `PUBLIC_CI_AUTOMERGE_ENABLED=true` only after those protections are
   confirmed.
5. Create a dedicated `ghrunner` macOS account with no personal credentials or
   unrelated checkouts. Register it with the `gs-decomp-public` label, build
   `gs-decomp-agent-pokestadiumgs:latest` from a clean public checkout, and
   verify one maintainer PR end-to-end.
6. Only after public validation succeeds, detach the existing private runner
   and begin the private-repository retirement process.

Do not require the ROM check until the workflow has reported successfully at
least once; otherwise every PR can be blocked waiting for a check that has not
yet been published.
