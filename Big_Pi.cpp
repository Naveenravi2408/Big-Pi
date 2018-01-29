#include <iostream>
#include <iomanip>
#include <mpir.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

const int MAX_ITERATIONS = 100;
const int PLACES         = 1000;        // desired decimal places
const int PRECISION      = PLACES + 1;  // +1 for the digit 3 before the decimal

const int BASE       = 10;  // base 10 numbers
const int BIT_COUNT  = 8;   // bits per machine word

const int BLOCK_SIZE = 10;                // print digits in blocks
const int LINE_SIZE  = 100;               // digits to print per line
const int BLK_PER_LINE = LINE_SIZE/BLOCK_SIZE; //number of blocks in a line
const int LINE_COUNT = PLACES/LINE_SIZE;  // lines to print
const int GROUP_SIZE = 5;                 // line grouping size


void cube_root(mpf_t& x, const mpf_t a);
void print(const mpf_t& pi);

/**
 * The main.
 */
int main()
{
    mpf_set_default_prec(BIT_COUNT*PRECISION);  // precision in bits

    mpf_t pi; mpf_init(pi);

// Constant values

    mpf_t one;
    mpf_init(one); mpf_set_str(one, "1", BASE);   //@param constant for number 1

    mpf_t two;
    mpf_init(two); mpf_set_str(two, "2", BASE);   //@param constant for number 2

    mpf_t three;
    mpf_init(three); mpf_set_str(three, "3", BASE); //@param constant for number 3

    mpf_t nine;
    mpf_init(nine); mpf_set_str(nine, "9", BASE);  //@param constant for number 9

    mpf_t two_seven;
    mpf_init(two_seven); mpf_set_str(two_seven, "27", BASE); //@param constant for number 27

//@param power_mult_ans is updating variable used in calculating an+1
    mpf_t power_mult_ans;
    mpf_init(power_mult_ans); mpf_set_str(power_mult_ans, "1" ,BASE);

//@param one_by_three is a constant used in calculating an+1
    mpf_t one_by_three;
    mpf_init(one_by_three);  mpf_div(one_by_three, one,three);

//initializing previous values of a,r and s to zero
    mpf_t a; mpf_init(a);
    mpf_t r; mpf_init(r);
    mpf_t s; mpf_init(s); mpf_set(s,one);


//Calculating previous values of a,r and s

             //a0;
              mpf_div(a, one,three);

              //r0;

              mpf_t sqrt_three; 			mpf_init(sqrt_three); mpf_sqrt(sqrt_three, three);
              mpf_t r_numerator; 			mpf_init(r_numerator);

              mpf_sub(r_numerator, sqrt_three, one);
              mpf_div(r, r_numerator,two);

              //s0;

              mpf_t rr; 					mpf_init(rr);
              mpf_t rrr; 					mpf_init(rrr);
              mpf_t one_minus_rrr; 			        mpf_init(one_minus_rrr);
              mpf_mul(rr, r,r);
              mpf_mul(rrr, rr,r);
              mpf_sub(one_minus_rrr, one, rrr);

              cube_root(s, one_minus_rrr);



//Declaring and initializing all the variables which are required to run the iteration


    //tn+1;
      mpf_t t_n_plus_one; 			mpf_init(t_n_plus_one);
      mpf_t two_r_n; 			        mpf_init(two_r_n);

     //un+1;
       mpf_t rxr;						mpf_init(rxr);
       mpf_t u_n_plus_one; mpf_init(u_n_plus_one); 		mpf_set(u_n_plus_one, one);
       mpf_t rr_plus_r; 				        mpf_init(rr_plus_r);
       mpf_t one_plus_rr_plus_r; 				mpf_init(one_plus_rr_plus_r);
       mpf_t nine_x_r; 						mpf_init(nine_x_r);
       mpf_t tempu;                                             mpf_init(tempu);

     //vn+1;
       mpf_t v_n_plus_one; 					        mpf_init(v_n_plus_one);
       mpf_t t_n_plus_one_sq; 						mpf_init(t_n_plus_one_sq);
       mpf_t u_n_plus_one_sq; 						mpf_init(u_n_plus_one_sq);
       mpf_t temp_t_u; 							mpf_init(temp_t_u);
       mpf_t temp_add_t; 						mpf_init(temp_add_t);

      //wn+1;
        mpf_t w_n_plus_one; 						mpf_init(w_n_plus_one);
        mpf_t ss; 							mpf_init(ss);
        mpf_t ss_plus_s; 						mpf_init(ss_plus_s);
        mpf_t ss_plus_s_plus_one; 					mpf_init(ss_plus_s_plus_one);
        mpf_t numerator_w; 						mpf_init(numerator_w);


       //an+1;
         mpf_t a_n_plus_one; 						mpf_init(a_n_plus_one);
         mpf_t w_n_plus_one_x_a; 					mpf_init(w_n_plus_one_x_a);
         mpf_t one_minus_w_n_plus_one; 				        mpf_init(one_minus_w_n_plus_one);
         mpf_t power_value; 						mpf_init(power_value);
         mpf_t power_value_mult; 					mpf_init(power_value_mult);

        //sn+1;
          mpf_t s_n_plus_one; 						mpf_init(s_n_plus_one);
          mpf_t one_minus_r; 						mpf_init(one_minus_r);
          mpf_t one_minus_r_sq; 					mpf_init(one_minus_r_sq);
          mpf_t one_minus_r_cub; 					mpf_init(one_minus_r_cub);
          mpf_t two_x_u_n; 						mpf_init(two_x_u_n);
          mpf_t t_plus_two_u_n; 					mpf_init(t_plus_two_u_n);
          mpf_t denominator_s; 						mpf_init(denominator_s);

        //rn+1;
          mpf_t r_n_plus_one; 						mpf_init(r_n_plus_one); mpf_set(r_n_plus_one, one);
          mpf_t s_n_plus_one_sq; 					mpf_init(s_n_plus_one_sq);
          mpf_t s_n_plus_one_cub; 					mpf_init(s_n_plus_one_cub);
          mpf_t one_minus_s_n_plus_one_cub; 		                mpf_init(one_minus_s_n_plus_one_cub);


//Iteration steps starts from here

    for(int j=1; j<=MAX_ITERATIONS; j++)
    {

    //COMPUTING tn+1;

    mpf_mul(two_r_n, two,r);                 // 2r*n
    mpf_add(t_n_plus_one, two_r_n,one);


    //COMPUTING un+1;

    mpf_mul(rxr, r,r);                            // r^2 = r*r
    mpf_add(rr_plus_r, rxr, r);                   // r^2 + r
    mpf_add(one_plus_rr_plus_r, rr_plus_r, one);  // 1 + r^2 + r
    mpf_mul(nine_x_r, r,nine);                    // 9 * r
    mpf_mul(tempu,nine_x_r,one_plus_rr_plus_r);
    cube_root(u_n_plus_one, tempu);

    //COMPUTING vn+1;

    mpf_mul(t_n_plus_one_sq,t_n_plus_one,t_n_plus_one);   // tn+1^2
    mpf_mul(temp_t_u, u_n_plus_one,t_n_plus_one);         // (un+1)*(tn+1)
    mpf_mul(u_n_plus_one_sq, u_n_plus_one,u_n_plus_one);  // un+1^2
    mpf_add(temp_add_t, t_n_plus_one_sq,temp_t_u);        // (tn+1^2)+((un+1)*(tn+1))
    mpf_add(v_n_plus_one, temp_add_t, u_n_plus_one_sq);

    //COMPUTING wn+1;

    mpf_mul(ss,s,s);                                     // s^2 = ss = s*s
    mpf_add(ss_plus_s, ss,s);                            // ss + s
    mpf_add(ss_plus_s_plus_one, ss_plus_s,one);          // ss + s + 1
    mpf_mul(numerator_w, ss_plus_s_plus_one,two_seven);
    mpf_div(w_n_plus_one, numerator_w,v_n_plus_one);

    //COMPUTING an+1;

    mpf_mul(w_n_plus_one_x_a, w_n_plus_one, a);           // (wn+1)*a
    mpf_sub(one_minus_w_n_plus_one, one, w_n_plus_one);   // 1 - wn+1
    mpf_mul(power_value, power_mult_ans, one_by_three);   // calculating 3^2n-1
    mpf_mul(power_value_mult,one_minus_w_n_plus_one, power_value); //calculating 3^2n-1
    mpf_add(a_n_plus_one, power_value_mult,w_n_plus_one_x_a);

    mpf_mul(power_mult_ans, power_mult_ans, nine);
    mpf_set(a, a_n_plus_one);   // updating value of a to an+1

    //COMPUTING sn+1;

    mpf_sub(one_minus_r, one, r);                        // 1 - r
    mpf_mul(one_minus_r_sq,one_minus_r,one_minus_r);     // (1 - r)^2
    mpf_mul(one_minus_r_cub,one_minus_r_sq,one_minus_r); // (1 - r)^3
    mpf_mul(two_x_u_n,two,u_n_plus_one);                 // 2 * un+1
    mpf_add(t_plus_two_u_n,t_n_plus_one,two_x_u_n);      // (tn+1) + (2 * un+1)
    mpf_mul(denominator_s, t_plus_two_u_n,v_n_plus_one);
    mpf_div(s_n_plus_one,one_minus_r_cub,denominator_s);

    mpf_set(s,s_n_plus_one);    // updating value of s to sn+1

    //COMPUTING rn+1;

    mpf_mul(s_n_plus_one_sq,s_n_plus_one,s_n_plus_one);       // (sn+1)^2 = (sn+1) * (sn+1)
    mpf_mul(s_n_plus_one_cub,s_n_plus_one_sq,s_n_plus_one);   // (sn+1)^3
    mpf_sub(one_minus_s_n_plus_one_cub, one, s_n_plus_one_cub); // 1 - (sn+1)^3
    cube_root(r_n_plus_one,one_minus_s_n_plus_one_cub);

    mpf_set(r,r_n_plus_one);    // updating value of r to rn+1

    }

    mpf_div(pi, one,a);  // pi = 1/a

    print(pi);           // calling a print function to print all the values of pi

    return 0;
}


/**
 * Compute the cube root of a positive integer.
 * @param x where to store the result.
 * @param a the number whose cube root to compute.
 */

/***
 * Followed Halley's method for computing cube root
 */
void cube_root(mpf_t& x, const mpf_t a)
{
	mpf_t two; mpf_init(two);
	mpf_init(two); mpf_set_str(two, "2", BASE); //Declaring a constant of value 2

	mpf_t three; mpf_init(three);
	mpf_init(three); mpf_set_str(three, "3", BASE);  //Declaring a constant of value 3

	mpf_div(x, a,three);  // setting initial value of x = a/3

	mpf_t xx; 			mpf_init(xx);         // x^2
	mpf_t xxx; 			mpf_init(xxx);        // x^3
	mpf_t two_a; 		mpf_init(two_a);      // 2*a
	mpf_t two_x_cube; 	mpf_init(two_x_cube); // 2*x^3
	mpf_t numerator; 	mpf_init(numerator);
	mpf_t denominator; 	mpf_init(denominator);
	mpf_t temp; 		mpf_init(temp);
	mpf_t xnext; 		mpf_init(xnext);

	for(int i=0; i<10; i++)
	{
		mpf_mul(xx,x,x) ;                   // x^2 = x * x
		mpf_mul(xxx,x,xx);                  // x^3 = x^2 * x

		mpf_mul(two_a, two, a);             // 2a = 2 * a

		mpf_mul(two_x_cube, two, xxx);      // 2 * x^3

		mpf_add(numerator,xxx,two_a);       // x^3 + 2a
		mpf_add(denominator,two_x_cube,a);  // 2x^3 + a

		mpf_div(temp,numerator,denominator);

		mpf_mul(xnext, x,temp);              // xnext has the result of cube root

		mpf_set(x,xnext);                    // x = xnext because to update in the main function
	}
}

/**
 * Printing function
 * to print out digits in blocks of 10 and group of 5 rows
 * 500 digits per row group
 *
 */
void print(const mpf_t& pi)
{
    char *str = NULL;
    mp_exp_t exp;
    char *ans= mpf_get_str(str, &exp, BASE, PRECISION, pi);  // converting the numbers to string

    cout << endl <<endl;

    cout << "3.";
    ans++;           // To print the values after the decimal point

    // Looping for each line
   for (int line = 1; line <= LINE_COUNT; line++)
    {
        // Looping for number of blocks in each line
        for (int block = 1; block <= BLK_PER_LINE; block++)
        {
        	// Looping for each block in a line
        	for (int value = 1; value<= BLOCK_SIZE; value++)
        	{
        	cout << *ans;
        	ans++;
        	}
        	cout << "  ";    //spacing between each block
        }
        cout << endl;
        cout << "  ";        //for spacing in the beginning of the line

        // To print a blank line after each group
        if(line == GROUP_SIZE)
        	{
        	cout << endl;
        	cout << "  ";
        	}
    }
}
