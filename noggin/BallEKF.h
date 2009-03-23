/**
 * BallEKF.h - Header file for the BallEKF class
 * All coordinates in C++ are in the local coordinate frame
 * We convert to the global frame when dealing with python
 *
 * @author Tucker Hermans
 */

#ifndef BallEKF_h_DEFINED
#define BallEKF_h_DEFINED
#include <boost/shared_ptr.hpp>

#include "EKF.h"
#include "VisualBall.h"
#include "EKFStructs.h"
#include "NBMath.h"
#include "NogginStructs.h"

// Parameters
#define ASSUMED_FPS 30.0
#define BETA_BALL 5. // How much uncertainty naturally grows per update
#define GAMMA_BALL 0.4 // How much ball velocity should effect uncertainty
#define BALL_EKF_DIMENSION 4 // Number of states in Ball EKF
#define BALL_MEASUREMENT_DIMENSION 2 // Number of dimensions in a measurement
#define CARPET_FRICTION -25 // 25 cm/s^2
#define BALL_DECAY_PERCENT 0.25

// Default initialization values
#define INIT_BALL_X 0.0f
#define INIT_BALL_Y 100.0f
#define INIT_BALL_X_VEL 0.0f
#define INIT_BALL_Y_VEL 0.0f
#define X_UNCERT_MAX 440.0f
#define Y_UNCERT_MAX 680.0f
#define VELOCITY_UNCERT_MAX 300.0
#define X_UNCERT_MIN 1.0e-6
#define Y_UNCERT_MIN 1.0e-6
#define VELOCITY_UNCERT_MIN 1.0e-6
#define INIT_X_UNCERT X_UNCERT_MAX
#define INIT_Y_UNCERT Y_UNCERT_MAX
#define INIT_X_VEL_UNCERT VELOCITY_UNCERT_MAX
#define INIT_Y_VEL_UNCERT VELOCITY_UNCERT_MAX
#define X_EST_MIN -600.0f
#define Y_EST_MIN -1000.0f
#define X_EST_MAX 600.0f
#define Y_EST_MAX 1000.0f
#define VELOCITY_EST_MAX 300.0f
#define VELOCITY_EST_MIN -300.0f

/**
 * Class for tracking of ball position and velocity.  Extends the abstract
 * EKF class.
 */
class BallEKF : public EKF<BallMeasurement, MotionModel, BALL_EKF_DIMENSION,
                           BALL_MEASUREMENT_DIMENSION>
{
public:

    // Constructors & Destructors
    BallEKF(float initX = INIT_BALL_X, float initY = INIT_BALL_Y,
            float initVelX = INIT_BALL_X_VEL,
            float initVelY = INIT_BALL_Y_VEL,
            float initXUncert = INIT_X_UNCERT,
            float initYUncert = INIT_Y_UNCERT,
            float initVelXUncert = INIT_X_VEL_UNCERT,
            float initVelYUncert = INIT_Y_VEL_UNCERT);
    virtual ~BallEKF() {}

    // Update functions
    void updateModel(VisualBall * ball, bool _useCartesian=false);
    void sawTeammateBall(BallMeasurement m);
    void sawBall(VisualBall * ball);

    // Getters
    /**
     * @return The current estimate of the ball x position
     */
    const float getXEst() const { return xhat_k(0); }

    /**
     * @return The current estimate of the ball y position
     */
    const float getYEst() const { return xhat_k(1); }

    /**
     * @return The current estimate of the ball x velocity
     */
    const float getXVelocityEst() const { return xhat_k(2); }

    /**
     * @return The current estimate of the ball y velocity
     */
    const float getYVelocityEst() const { return xhat_k(3); }

    /**
     * @return The current uncertainty for ball x position
     */
    const float getXUncert() const { return P_k(0,0); }

    /**
     * @return The current uncertainty for ball y position
     */
    const float getYUncert() const { return P_k(1,1); }

    /**
     * @return The current uncertainty for ball x velocity
     */
    const float getXVelocityUncert() const { return P_k(2,2); }

    /**
     * @return The current uncertainty for ball y velocity
     */
    const float getYVelocityUncert() const { return P_k(3,3); }

    // Setters
    /**
     * @param val The new estimate of the ball x position
     */
    void setXEst(float val) { xhat_k(0) = val; }

    /**
     * @param val The new estimate of the ball y position
     */
    void setYEst(float val) { xhat_k(1) = val; }

    /**
     * @param val The new estimate of the ball x velocity
     */
    void setXVelocityEst(float val) { xhat_k(2) = val; }

    /**
     * @param val The new estimate of the ball y velocity
     */
    void setYVelocityEst(float val) { xhat_k(3) = val; }

    /**
     * @param val The new uncertainty for ball x position
     */
    void setXUncert(float val) { P_k(0,0) = val; }

    /**
     * @param val The new uncertainty for ball y position
     */
    void setYUncert(float val) { P_k(1,1) = val; }

    /**
     * @param val The new uncertainty for ball x velocity
     */
    void setXVelocityUncert(float val) { P_k(2,2) = val; }

    /**
     * @param val The new uncertainty for ball y velocity
     */
    void setYVelocityUncert(float val) { P_k(3,3) = val; }

    // Output methods
    friend std::ostream& operator<< (std::ostream &o, const BallEKF &c) {
        return o << "Est: (" << c.getXEst() << ", " << c.getYEst() << ", "
                 << c.getXVelocityEst() << ", " << c.getYVelocityEst() << ")\t"
                 << "Uncert: (" << c.getXUncert() << ", " << c.getYUncert()
                 << ", "
                 << c.getXVelocityUncert() << ", " << c.getYVelocityUncert()
                 << ")";
    }
private:
    // Core Functions
    virtual StateVector associateTimeUpdate(MotionModel u_k);
    virtual void incorporateMeasurement(BallMeasurement z,
                                        StateMeasurementMatrix &H_k,
                                        MeasurementMatrix &R_k,
                                        MeasurementVector &V_k);
    void limitAPrioriEst(void);
    void limitPosteriorEst(void);
    void limitAPrioriUncert(void);
    void limitPosteriorUncert(void);
    bool useCartesian;
};
#endif // File
