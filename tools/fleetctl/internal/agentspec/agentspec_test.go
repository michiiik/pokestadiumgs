package agentspec

import (
	"testing"
	"time"
)

func TestParse(t *testing.T) {
	cases := []struct {
		in   string
		want Spec
	}{
		{"codex:gpt-5.6-luna:high", Spec{"codex", "gpt-5.6-luna", "high"}},
		{"kimi:kimi-code/k3:high", Spec{"kimi", "kimi-code/k3", "high"}},
		{"alibaba:qwen3.7-max", Spec{"alibaba", "qwen3.7-max", ""}},
		{"claude:sonnet", Spec{"claude", "sonnet", ""}},
	}
	for _, c := range cases {
		got, err := Parse(c.in)
		if err != nil {
			t.Fatalf("Parse(%q): %v", c.in, err)
		}
		if got != c.want {
			t.Fatalf("Parse(%q) = %+v, want %+v", c.in, got, c.want)
		}
		if got.String() != c.in {
			t.Fatalf("Spec(%+v).String() = %q, want %q", got, got.String(), c.in)
		}
	}
}

func TestParseErrors(t *testing.T) {
	for _, in := range []string{"", "codex", "codex:", ":sonnet", "a:b:c:d", "a::c"} {
		if _, err := Parse(in); err == nil {
			t.Fatalf("Parse(%q): want error, got nil", in)
		}
	}
}

func TestEnv(t *testing.T) {
	s := Spec{Agent: "codex", Model: "gpt-5.6-luna", Effort: "high"}
	env := s.Env()
	if env["AGENT"] != "codex" || env["GENERATOR_MODEL"] != "gpt-5.6-luna" || env["GENERATOR_EFFORT"] != "high" {
		t.Fatalf("Env() = %+v", env)
	}

	s2 := Spec{Agent: "claude", Model: "sonnet"}
	env2 := s2.Env()
	if _, ok := env2["GENERATOR_EFFORT"]; ok {
		t.Fatalf("Env() should omit GENERATOR_EFFORT when Effort is empty: %+v", env2)
	}
}

func TestParseKeyDuration(t *testing.T) {
	agent, d, err := ParseKeyDuration("kimi=5h")
	if err != nil {
		t.Fatal(err)
	}
	if agent != "kimi" || d != 5*time.Hour {
		t.Fatalf("got (%q, %v)", agent, d)
	}
	if _, _, err := ParseKeyDuration("kimi"); err == nil {
		t.Fatal("want error for missing '='")
	}
	if _, _, err := ParseKeyDuration("kimi=notaduration"); err == nil {
		t.Fatal("want error for bad duration")
	}
}

func TestParseKeyInt(t *testing.T) {
	agent, n, err := ParseKeyInt("codex=2")
	if err != nil {
		t.Fatal(err)
	}
	if agent != "codex" || n != 2 {
		t.Fatalf("got (%q, %d)", agent, n)
	}
	for _, bad := range []string{"codex", "codex=0", "codex=-1", "codex=x"} {
		if _, _, err := ParseKeyInt(bad); err == nil {
			t.Fatalf("ParseKeyInt(%q): want error", bad)
		}
	}
}
