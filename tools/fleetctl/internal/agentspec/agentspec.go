// Package agentspec parses the "agent:model[:effort]" spec format used on
// the fleetctl command line, e.g. "codex:gpt-5.6-luna:high",
// "kimi:kimi-code/k3:high", "alibaba:qwen3.7-max", "claude:sonnet". It also
// parses the "KEY=VALUE" forms used by --cooldown and --agent-concurrency.
package agentspec

import (
	"fmt"
	"strconv"
	"strings"
	"time"
)

// Spec identifies one coding agent + model + optional effort, matching
// docs/CONTAINER_AGENT.md sec 3's AGENT/GENERATOR_MODEL/GENERATOR_EFFORT
// triple. Effort is empty when the spec has only two fields.
type Spec struct {
	Agent  string `json:"agent"`
	Model  string `json:"model"`
	Effort string `json:"effort,omitempty"`
}

// Parse reads "agent:model" or "agent:model:effort". The model field may
// itself contain "/" (e.g. "kimi-code/k3") but never ":", so splitting on
// ":" is unambiguous.
func Parse(s string) (Spec, error) {
	parts := strings.Split(s, ":")
	switch len(parts) {
	case 2:
		if parts[0] == "" || parts[1] == "" {
			return Spec{}, fmt.Errorf("agentspec: empty field in %q", s)
		}
		return Spec{Agent: parts[0], Model: parts[1]}, nil
	case 3:
		if parts[0] == "" || parts[1] == "" || parts[2] == "" {
			return Spec{}, fmt.Errorf("agentspec: empty field in %q", s)
		}
		return Spec{Agent: parts[0], Model: parts[1], Effort: parts[2]}, nil
	default:
		return Spec{}, fmt.Errorf(
			"agentspec: want \"agent:model\" or \"agent:model:effort\", got %q", s)
	}
}

// String renders the spec back to its command-line form.
func (s Spec) String() string {
	if s.Effort != "" {
		return fmt.Sprintf("%s:%s:%s", s.Agent, s.Model, s.Effort)
	}
	return fmt.Sprintf("%s:%s", s.Agent, s.Model)
}

// Env returns the AGENT/GENERATOR_MODEL/GENERATOR_EFFORT environment
// container/run.sh (docs/CONTAINER_AGENT.md sec 3) expects for this spec.
func (s Spec) Env() map[string]string {
	env := map[string]string{
		"AGENT":           s.Agent,
		"GENERATOR_MODEL": s.Model,
	}
	if s.Effort != "" {
		env["GENERATOR_EFFORT"] = s.Effort
	}
	return env
}

// ParseKeyDuration parses "kimi=5h" into ("kimi", 5h) -- the --cooldown
// flag's form.
func ParseKeyDuration(s string) (string, time.Duration, error) {
	key, value, ok := strings.Cut(s, "=")
	if !ok || key == "" || value == "" {
		return "", 0, fmt.Errorf("agentspec: want \"agent=duration\", got %q", s)
	}
	d, err := time.ParseDuration(value)
	if err != nil {
		return "", 0, fmt.Errorf("agentspec: bad duration in %q: %w", s, err)
	}
	return key, d, nil
}

// ParseKeyInt parses "codex=2" into ("codex", 2) -- the --agent-concurrency
// flag's form.
func ParseKeyInt(s string) (string, int, error) {
	key, value, ok := strings.Cut(s, "=")
	if !ok || key == "" || value == "" {
		return "", 0, fmt.Errorf("agentspec: want \"agent=N\", got %q", s)
	}
	n, err := strconv.Atoi(value)
	if err != nil || n <= 0 {
		return "", 0, fmt.Errorf("agentspec: bad concurrency in %q", s)
	}
	return key, n, nil
}
