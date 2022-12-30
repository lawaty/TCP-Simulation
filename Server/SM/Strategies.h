// This file must be included inside SM.h

/**
 * Abstract base class for state stratigies
 */
class Strategy
{
public:
  /**
   * Init state parameters
   */
  init(State *state)
  {
    state->cwnd = MSS;
    state->ssthresh = 64;
    state->on_flight = 0;
    state->dupAcks = 0;
  }

  virtual void newAck(State *);         // on ack received
  virtual void timeout(State *);        // on timeout
  virtual void duplicate(State *);      // on duplicate ACK received
  virtual void threshExceeded(State *); // on crossing ssthresh limit
};

class SlowStart : Strategy
{
  void newAck(State *)
  {
    state->cwnd += MSS;
    state->dupAcks = 0;
  }

  void timeout(State *)
  {
    
  }
}