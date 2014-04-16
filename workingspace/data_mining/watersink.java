import java.io.*;
import java.util.*;
/*
 * Twitter interview problem
 * calculate how much water a sink can hold. The arrage represent the height of the sink wall. The water can be held
 * in the gap between walls. So an algorithm should be designed to calculate how much water the sink could hold. 
 *	Author: Xuan Wang
 *  Input: an array of wall height
 *  Output: the capacity of the water the sink can hold
 *  Seems like a dynamic programming problem 
 *
*/

public class watersink
{
	int [] sink ={3,0,8,5,6,9,7,0,2,0,2};  // the walls
	
	public int find_r_max(int start)       // find the highest wall on the right hand side
	{
		int ind = start+1;
		int tmp = sink[ind];
		for(int i =ind;i<sink.length;i++)
		{
			if(tmp<sink[i])
			{
				tmp = sink[i];
				ind = i; 
			}		
		}
		return ind;
	}


	public int find_l_max(int start)       // find the highest wall on the left hand side
	{
		int ind = start-1;
		int tmp = sink[ind];
		for(int i = ind; i>=0; i--)
		{
			if(tmp<sink[i])
			{
				tmp = sink[i];
				ind = i;
			}	
		}
		return ind;	
	}
	
	public int compute_left(int ind)        // compute how much water the sink can hold on the left hand side
	{
		if(ind ==0)
		{
			return 0;
		}
		int ind_2 = find_l_max(ind);
		int value =0;
		if(ind-ind_2>1)
		{
			for(int i =ind-1;i>=ind_2;i--)
			{
				
				value = value + sink[ind_2]-sink[i]; 
			}
			
		}
		value = value + compute_left(ind_2);       // recursion, subproblem
		return value;
	}

	public int compute_right(int ind)        // compute water amount the sink hold on the right hand side
	{
		if(ind == sink.length-1)
		{
			return 0;
		}
		int ind_2 = find_r_max(ind);
		int value = 0;
		if(ind_2-ind>1)
		{
			for(int i = ind+1;i<=ind_2;i++)
			{
				value = value + sink[ind_2]-sink[i];
			}
		}
		value = value + compute_right(ind_2);
		return value;

	}


	public int compute_water(int ind)
	{
		return compute_left(ind)+compute_right(ind);		// add left and right togeter! And Bang!
	}

	public static void main(String [] argv)
	{
		watersink a = new watersink();	
		int ind = a.find_r_max(0);
		int value = a.compute_water(ind);
		System.out.printf("the sink can hold water :  %d l",value);		
	}
       
}