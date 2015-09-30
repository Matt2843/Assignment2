dp ALU(in a,b : tc(32); in select : ns(2); out r : tc(32); out N, Z : ns(1)) {
	always {
		r = (select == 0) ? a - b : 
			(select == 1) ? b - a :
			(select == 2) ? a : b;

		N = (r < 0) ? 1 : 0;
		Z = (r == 0) ? 1 : 0;	
	}
}

dp testALU(out A, B : tc(32); out select : ns(2); in R : tc(32); in N, Z : ns(1)) {
	always{
		$display($dec, "Cycle: ", $cycle, " Input: ", A,"/", B, ", Select: ", select, ", R: ", R, ", N: ", N, ", Z: ", Z);
	}

	sfg test_0 { A = 1; B = 1; select = 0; }
	sfg test_1 { A = 2; B = 1; select = 1; }
	sfg test_2 { A = 1; B = 2; select = 2; }
	sfg test_3 { A = 1; B = 2; select = 3; }
}

 // note : State machine to control the adder testbench.
fsm f_testbench(testALU) {
	initial s0; 				// begin with state s0
	state s1, s2, s3;			// other states are: s1, s2
	@s0 (test_0) -> s1; 		// run test_0 and go to s1
	@s1 (test_1) -> s2; 		// run test_1 and go to s2
	@s2 (test_2) -> s3; 		// run test_2 and go to s3
	@s3 (test_3) -> s0;			// run test_3 and go to s0
}

system myFirstSystem {
	ALU(A, B, select, R, N, Z);
	testALU(A, B, select, R, N, Z);
}