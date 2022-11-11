struct input { 
        float a; 
        int Y<>;
};

struct avg {
	float avgrs;
};

struct min_max {
	int mm<2>;
};

struct mult {
	float mulrs<>;
};

program RES_PROG {
	version RES_VERS {
		avg RPC_AVG(input) = 1;
		min_max RPC_MM(input) = 2;
		mult RPC_MULT(input) = 3;
        } = 1;
} = 0x23451112;

