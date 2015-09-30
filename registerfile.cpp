dp registerfile(in asel, bsel, storesel : ns(3); in storeenable : ns(1); in storedata : tc(32); out a, b : tc(32)) {
	reg r1,r2,r3,r4,r5,r6,r7 : tc(32);
	always {
		a = (asel == 0) ? 0 : 
			(asel == 1) ? r1 :
			(asel == 2) ? r2 :
			(asel == 3) ? r3 :
			(asel == 4) ? r4 :
			(asel == 5) ? r5 :
			(asel == 6) ? r6 : r7;

		b = (bsel == 0) ? 0 : 
			(bsel == 1) ? r1 :
			(bsel == 2) ? r2 :
			(bsel == 3) ? r3 :
			(bsel == 4) ? r4 :
			(bsel == 5) ? r5 :
			(bsel == 6) ? r6 : r7;

		
		r1 = (storesel == 1 & storeenable) ? storedata : r1;
		r2 = (storesel == 2 & storeenable) ? storedata : r2;
		r3 = (storesel == 3 & storeenable) ? storedata : r3;
		r4 = (storesel == 4 & storeenable) ? storedata : r4;
		r5 = (storesel == 5 & storeenable) ? storedata : r5;
		r6 = (storesel == 6 & storeenable) ? storedata : r6;
		r7 = (storesel == 7 & storeenable) ? storedata : r7;


		// (~storeenable) ? 0 :
		// (storesel == 0) ? 0 :
		// (storesel == 1) ? r1 = storedata :
		// (storesel == 2) ? r2 = storedata :
		// (storesel == 3) ? r3 = storedata :
		// (storesel == 4) ? r4 = storedata :
		// (storesel == 5) ? r5 = storedata :
		// (storesel == 6) ? r6 = storedata : 
		// (storesel == 7) ? r7 = storedata : 0;

	}
}

dp testRegisterfile(out asel, bsel, storesel : ns(3); out storeenable : ns(1); out storedata : tc(32); in a, b : tc(32)) {
	always{
		$display($dec, "Cycle: ", $cycle, ", a: ", a, ", b: ", b);
	}

	sfg test_0 { asel = 1; bsel = 2; storesel = 1; storeenable = 1; storedata = 5; }
	sfg test_1 { asel = 1; bsel = 2; storesel = 2; storeenable = 1; storedata = 4; }
	sfg test_2 { asel = 1; bsel = 2; storesel = 0; storeenable = 0; storedata = 0; }
	sfg test_3 { asel = 1; bsel = 2; storesel = 0; storeenable = 0; storedata = 0; }
}

 // note : State machine to control the adder testbench.
fsm f_testbench(testRegisterfile) {
	initial s0; 				// begin with state s0
	state s1, s2, s3;			// other states are: s1, s2
	@s0 (test_0) -> s1; 		// run test_0 and go to s1
	@s1 (test_1) -> s2; 		// run test_1 and go to s2
	@s2 (test_2) -> s3; 		// run test_2 and go to s3
	@s3 (test_3) -> s0;			// run test_3 and go to s0
}

system myFirstSystem {
	registerfile(asel, bsel, storesel, storeenable, storedata, a, b);
	testRegisterfile(asel, bsel, storesel, storeenable, storedata, a, b);
}