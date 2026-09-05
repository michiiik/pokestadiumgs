#!/bin/bash
# One-click re-authentication for the gemini generator (Google Antigravity
# CLI / `agy`) on macOS. Double-click this file in Finder, or run it
# directly: bash container/generators/gemini_login_macos.command
#
# Why this exists: container/run.sh mounts a portable credential file
# (~/.gemini/antigravity-cli/antigravity-oauth-token) into every gemini
# container -- see gemini.sh and README.md in this directory. On macOS,
# `agy` binds its own credential to Keychain instead of writing that file,
# so a native macOS login (or `security dump-keychain`) never produces it.
# The one supported way to get the portable file is to complete the real
# OAuth login inside a Linux environment -- this script does that inside
# the same image container/run.sh actually launches gemini containers
# from, then copies the result to where run.sh already looks for it.
#
# This is NOT a Keychain-extraction shortcut -- it always goes through a
# real interactive Google OAuth consent (open the URL, sign in, grant
# consent), same as the manual process documented in README.md. It cannot
# be fully silent because that consent step is a real human-in-the-loop
# step; this script automates everything around it (opening the URL,
# copying the result into place) so you only have to do that one step.
#
# Run this whenever gemini containers start failing with
# "antigravity-oauth-token missing" or "generator_exhausted" immediately
# on launch -- that means this credential expired or was never set up on
# this machine. No fleetctl restart needed afterward: container/run.sh
# reads the token file fresh on every container launch.

set -euo pipefail

IMAGE="${GS_DECOMP_IMAGE:-gs-decomp-agent:latest}"
VOLUME="gemini-login-home"

echo "== gemini re-auth: starting login flow in $IMAGE =="
echo "   a Google OAuth URL will open in your browser automatically --"
echo "   sign in, grant consent, then paste the authorization code back"
echo "   into THIS window when prompted."
echo

# Only stdout is piped through the URL-watching loop below; stdin is
# inherited from this terminal untouched, so pasting the authorization
# code back still reaches the container normally.
docker run -i --rm --entrypoint /bin/bash \
  -v "$VOLUME:/root/.gemini" \
  "$IMAGE" -c 'agy -p "reply with exactly: OK" --model gemini-3.8-flash-medium --output-format text --dangerously-skip-permissions' \
  | while IFS= read -r line; do
    printf '%s\n' "$line"
    if [[ "$line" == *"https://"* ]]; then
      url=$(printf '%s\n' "$line" | grep -oE 'https://[^ ]+' | head -1)
      if [[ -n "$url" ]]; then
        open "$url" >/dev/null 2>&1 || true
      fi
    fi
  done

echo
echo "== login flow finished -- copying the credential onto the host =="

mkdir -p "$HOME/.gemini/antigravity-cli" "$HOME/.gemini/config/projects"

docker run --rm -v "$VOLUME:/root/.gemini" -v "$HOME/.gemini:/hostgemini" \
  --entrypoint /bin/bash "$IMAGE" -c "
    set -e
    cp /root/.gemini/antigravity-cli/antigravity-oauth-token /hostgemini/antigravity-cli/
    cp /root/.gemini/antigravity-cli/installation_id /hostgemini/antigravity-cli/
    cp /root/.gemini/config/config.json /hostgemini/config/
    cp /root/.gemini/config/projects/default-cli-project.json /hostgemini/config/projects/
    chown -R $(id -u):$(id -g) /hostgemini/antigravity-cli /hostgemini/config
  "

if [[ -f "$HOME/.gemini/antigravity-cli/antigravity-oauth-token" ]]; then
  echo
  echo "== done: ~/.gemini/antigravity-cli/antigravity-oauth-token is in place =="
  echo "   every future gemini container picks this up automatically via"
  echo "   container/run.sh's existing mount logic -- no restart needed."
else
  echo
  echo "== something went wrong -- token file not found on host, check the output above =="
  exit 1
fi

echo
read -r -p "Press Enter to close this window..." _ || true
