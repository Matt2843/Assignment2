ipblock instmem(in address : ns(5);
				in wr,rd   : ns(1);
				in idata   : ns(32);
				out odata  : ns(32)) {
	iptype "ram";
	ipparm "size=64";
	ipparm "wl=32";
	ipparm "file=program.txt";
}


dp testInstmem(out address : ns(5); out wr,rd : ns(1); out idata : ns(32); in odata : ns(32)) {
	always {
		$display($dec, "Address: ", address, ", odata: ", odata);
	}
	sfg test_0 { address = 0; wr = 0; rd = 1; idata = 0; }
	sfg test_1 { address = 0; wr = 1; rd = 0; idata = 20340; }
	sfg test_2 { address = 10; wr = 0; rd = 1; idata = 0; }
	sfg test_3 { address = 0; wr = 0; rd = 0; idata = 0; }
}

 // note : State machine to control the adder testbench.
fsm f_testbench(testInstmem) {
	initial s0; 				// begin with state s0
	state s1, s2, s3;			// other states are: s1, s2
	@s0 (test_0) -> s1; 		// run test_0 and go to s1
	@s1 (test_1) -> s2; 		// run test_1 and go to s2
	@s2 (test_2) -> s3; 		// run test_2 and go to s3
	@s3 (test_3) -> s0;			// run test_3 and go to s0
}

system sys {
	instmem(address, wr, rd, idata, odata);
	testInstmem(address, wr, rd, idata, odata);
}