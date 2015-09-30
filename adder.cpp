dp adder(in a, b : tc(32); out r : tc(32)) {
	always {
		r = a + b;
	}
}

dp testAdder(out A, B : tc(32); in R : tc(32)) {
	always{
		$display($dec, "Cycle:", $cycle, ", A=", A , ", B=", B , ", R=", R);
	}

	sfg test_0 { A=3; B=6; }
	sfg test_1 { A=23; B=17; }
	sfg test_2 { A=12; B=0; }
}

 // note : State machine to control the adder testbench.
fsm f_testbench(testAdder) {
	initial s0; 				// begin with state s0
	state s1, s2; 				// other states are: s1, s2
	@s0 (test_0) -> s1; 		// run test_0 and go to s1
	@s1 (test_1) -> s2; 		// run test_1 and go to s2
	@s2 (test_2) -> s0; 		// run test_2 and go to s0
}

system myFirstSystem {
	adder(A, B, R);
	testAdder(A, B, R);
}