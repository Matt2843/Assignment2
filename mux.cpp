dp mux(in a, b : tc(32); in select : ns(1); out r : tc(32)) {
	always {
		r = (~select) ? a : b;
	}
}

dp testMux(out a, b : tc(32); out select : ns(1); in r : tc(32)) {
	always {
		$display($dec, "Cycle: ", $cycle, " Input: ", a,"/", b, ", Select: ", select, ", R: ", r);
	}

	sfg test_a { a = 12; b = 10; select = 1;}
	sfg test_b { a = 12; b = 10; select = 0;}
	sfg test_c { a = 5; b = 7; select = 1;}
}

 // note : State machine to control the adder testbench.
fsm f_testbench(testMux) {
	initial s0; 				// begin with state s0
	state s1, s2; 				// other states are: s1, s2
	@s0 (test_a) -> s1; 		// run test_0 and go to s1
	@s1 (test_b) -> s2; 		// run test_1 and go to s2
	@s2 (test_c) -> s0; 		// run test_2 and go to s0
}

system myFirstSystem {
	mux(a, b, select, r);
	testMux(a, b, select, r);
}