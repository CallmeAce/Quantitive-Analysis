#include <stdio.h>
#include <cstdio>


struct State
{
	int NSIDE;
	int* pos;


	State(int NSIDE)
	{
		this->NSIDE = NSIDE;
		this->pos = new int[NSIDE];
	}

	~State()
	{
		delete this->pos;
	}	

	void print()
	{
		static int sol = 0;

		printf("Sol #%d:", ++sol);
		for(int i = 0; i < NSIDE; ++i) printf(" %d", pos[i]);
		printf("\n");

		for(int i = 0; i < NSIDE; ++i)
		{
			for(int j = 0; j < NSIDE; ++j)
				if(pos[i] == j)
					printf("R ");
				else
					printf("* ");

			printf("\n");
		}

		printf("\n");
	}

	bool attacks(int pA, int pB)
	{
		int tmp = pA - pB;
		if(pos[pA] == pos[pB]) 
			return true;
		if(tmp == pos[pA] - pos[pB]) 
			return true;
												
		if(tmp == pos[pB] - pos[pA]) 
			return true;
														
		return false;

	}
	
		ioid search(int n)
		// Checks if any queen attacks another
		bool attacks(int n)
		{
			for(int i = 0; i < n; ++i)
				for(int j = i + 1; j < n; ++j)
					if(attacks(i, j))
						return true;
			return false;
					
		}
			
			// Search for a solution using backtracking
		void search(int n)
		{	
			if(n != NSIDE)
			{
				for(int i = 0; i < NSIDE; ++i)
				{
					pos[n] = i;
					if(!attacks(n + 1))
						search(n + 1);
				}
			}
			else
			print();
		}
};

tatic int sol = 0;
		
		printf("Sol #%d:", ++sol);
		for(int i = 0; i < NSIDE; ++i) printf(" %d", pos[i]);
		printf("\n");
		
		for(int i = 0; i < NSIDE; ++i)
		{
						for(int j = 0; j < NSIDE; ++j)
											if(pos[i] == j)
																	printf("R ");
										else
																printf("* ");
											
									printf("\n");
											}
		
		printf("\n");
	}
	nt main(int argc, char* argv[])
{
	int NSIDE;
	scanf("%d", &NSIDE);

	State init(NSIDE);
	init.search(0);

	return 0;
}
