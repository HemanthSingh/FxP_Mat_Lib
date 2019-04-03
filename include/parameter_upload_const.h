/*
 * parameter_upload_const.h
 *
 * Created: 11-8-2012 18:16:18
 *  Author: Leon
 */ 


#ifndef PARAMETER_UPLOAD_CONST_H_
#define PARAMETER_UPLOAD_CONST_H_


// ***********************************************************************************************************************************************************
// ** Non uploadable constant parameters
// ***********************************************************************************************************************************************************

// ** Basic set (ARM9 and XMEGA)

#define MTM_BUFFER_LENGTH				4														// total amount of messages to store before overwriting the oldest (i.e. ringbuffer size)
#define MTM_MEAS_DURATION_MIN_us		3000UL													// minimal duration of measurement (used for drdy callback validity check)
#define MTM_MEAS_DURATION_MAX_us		8000UL													// maximal duration of measurement (used for scheduled callback backup)
#define MTM_MEAS_TIMEOUT_MAX_us			16000UL													// duration after which the wait loop is ended on a timeout condition
																								// the measurement is considered finished (i.e. continuously missed interrupts assumed)

#define MTM_BM_FIELD_EXPECTED_CENTER_X				(116E-6)									// [T]; expected bias measurement center value (any offset is added to this)
#define MTM_BM_FIELD_EXPECTED_CENTER_Y				(116E-6)									// [T]; expected bias measurement center value (any offset is added to this)
#define MTM_BM_FIELD_EXPECTED_CENTER_Z				(108E-6)									// [T]; expected bias measurement center value (any offset is added to this)

#define MTQ_ACTIVATION_DURATION_LOWER_THRESHOLD_X		TSRV_US_TO_TICKS(500)					// torqueing for this axis is skipped if duration is below this threshold
#define MTQ_ACTIVATION_DURATION_LOWER_THRESHOLD_Y		TSRV_US_TO_TICKS(500)
#define MTQ_ACTIVATION_DURATION_LOWER_THRESHOLD_Z		TSRV_US_TO_TICKS(500)

#define MDET_FIXED_MTQ_ON_TO_MTM_MEAS_ticks				TSRV_US_TO_TICKS(500)					// amount of ticks after MTQ_ON to wait until MTQ_ON magnetometer measurement
#define MDET_FIXED_MTM_MEAS_CYCLE_ticks					TSRV_US_TO_TICKS(10000)					// amount of ticks of each detumble MTM measurement cycle
#define MDET_FIXED_MTM_BIAS_CYCLE_ticks					TSRV_US_TO_TICKS(6000)					// amount of ticks of each detumble bias measurement cycle

// ** Advanced set (only ARM9)

#define ACON_RADPS_PER_ROTPM (0.10471975511966)	// [rad/rpm]; conversion between rpm and rad/s ( [(rad)/s] = 2*pi [(rad)] * (1 [min] / 60 [s]) * [(rot)/min])

// satellite rotational inertia
#define ACON_SAT_J_c0		(0.055)				// [kg m^2]; TODO: fill in right values
#define ACON_SAT_J_c1		(0.0)
#define ACON_SAT_J_c2		(0.0)
#define ACON_SAT_J_c3		(0.0)
#define ACON_SAT_J_c4		(0.055)
#define ACON_SAT_J_c5		(0.0)
#define ACON_SAT_J_c6		(0.0)
#define ACON_SAT_J_c7		(0.0)
#define ACON_SAT_J_c8		(0.017)
//new Inv comp
#define ACON_INV_J_c0		(18.1818)
#define ACON_INV_J_c4		(18.1818)
#define ACON_INV_J_c8		(58.8235)

// reaction wheel rotational inertia
#define ACON_RW_J_X			(2.95E-7)	// [kg m^2]
#define ACON_RW_J_Y			(2.95E-7)
#define ACON_RW_J_Z			(2.95E-7)

#define ADET_MAT_EXP_TERMS	20

#define ADET_COVMAT_INIT_DIAG_F1				(double)1e-2		// [-];				first 4 diagonal entries
#define ADET_COVMAT_INIT_DIAG_F2				(double)1e-2
#define ADET_COVMAT_INIT_DIAG_F3				(double)1e-2
#define ADET_COVMAT_INIT_DIAG_F4				(double)1e-2
#define ADET_COVMAT_INIT_DIAG_L1				(double)1e-2	// [deg^2/s^2];		last 3 diagonal entries
#define ADET_COVMAT_INIT_DIAG_L2				(double)1e-2
#define ADET_COVMAT_INIT_DIAG_L3				(double)1e-2


#define ADET_SIGMA_MTM							0.066666666666667		// [-]
#define ADET_SIGMA_SS							0.052359877559830		// [deg/s]

#define MFSP_EARTH_AXIS_TILT					(23.44 * GC_RAD_DEG) 		// [rad]

#define MFSP_DURATION_YEAR_s					31557600.
#define MFSP_DURATION_SIDEREAL_DAY_s			86163.9

// buffer time to ensure that the torque time used in the dipole computation is available
// when the execution has returned to the attitude control main function that will enable the torquers
#define ACON_DETDIPOLE_TO_MTQON_BUFFER_ticks	(TSRV_US_TO_TICKS(1000UL))



#endif /* PARAMETER_UPLOAD_CONST_H_ */
