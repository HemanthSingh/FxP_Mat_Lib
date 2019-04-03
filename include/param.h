/*
 * param.h
 *
 * Created: 19-04-2018 22:23:49
 *  Author: HS Jagadeeshwar
 */ 
#define alphaBdot  1/1200
#define Bdotnrmavg0  1e-7
#define Gain_Bdot  1*50000
#define BdotLowTreshold  9.4e-7  //nanoTesla per second. 
#define BdotHighTreshold  10*5e-7
#define Bdot_counter (uint16_t)(12000/2)+1
#define p_adet_k 7.808124487244419e-04
#define p_adet_d 0.027943021467344
#define h_max 7.5e-4                  //Maximal angular momentum (one sided)
#define h_min 3e-6
#define h_goal 0.0*7.5e-4
#define h_dot_steps (double)300     //% at least 300 rpm change can be requested per second.
#define m_steps (double)30000
#define ul_trig_on (double)2.250000000000000e-04
#define ul_trig_off (double)2.250000000000000e-04
// (Dt-t_meas)/Dt
//t_meas = 0.1;               % Measurement time (MTQ disipate)
//Dt = 2
#define t_mtq 0.95
#define h_dot_max (double)8.999999999999999e-06
#define m_max (double)0.060000000000000
#define t_error  (double)3.0
#define q0a	(double)0.8045
#define q0b	(double)-0.2838
#define q0c	(double)-0.1490
#define q0d	(double)0.5000
#define omega_est_a    (double)-0.0008
#define omega_est_b    (double)0.0034
#define omega_est_c    (double)-0.0026
//Kepler parameters
#define incl (double)1.706932008450454    //deg2rad(97.8)
#define RAAN (double)0.698131700797732    //deg2rad(40)
#define a_param (double)6978	//R +altitude
#define	T_orb (double)5.801060945588950e+03	//Orbital period [s]
#define	ecc (double)0.0
#define theta0 (double)0.0
#define ECEFECI0 -1.57
#define omega (double)0.0
#define T_sid (double)8.616393442622952e+04  // Sidereal day [sec]

//Proc noise
#define sigma_q_p	(double)4e-4//5e-4
#define sigma_omega_p (double)4e-4//4e-5

