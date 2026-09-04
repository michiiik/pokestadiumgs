package main

import "testing"

// TestValidateStopFlags pins the "exactly one of --run/--all" contract
// directly: the ordinary single-flag cases must succeed (the real bug --
// `fleetctl stop --run <id>` and `fleetctl stop --all` both always errored
// with "exactly one of --run ID or --all is required", because the
// original inline check compared *run == "" against *all instead of
// *run != "" against *all), and the two genuinely invalid combinations
// (neither given, both given) must still error.
func TestValidateStopFlags(t *testing.T) {
	cases := []struct {
		name    string
		run     string
		all     bool
		wantErr bool
	}{
		{"only --run", "x-p0", false, false},
		{"only --all", "", true, false},
		{"neither given", "", false, true},
		{"both given", "x-p0", true, true},
	}
	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			err := validateStopFlags(c.run, c.all)
			if c.wantErr && err == nil {
				t.Fatalf("validateStopFlags(%q, %v) = nil, want an error", c.run, c.all)
			}
			if !c.wantErr && err != nil {
				t.Fatalf("validateStopFlags(%q, %v) = %v, want nil", c.run, c.all, err)
			}
		})
	}
}
