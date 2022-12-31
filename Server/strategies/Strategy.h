// #define STRATEGY

typedef struct
{
  int cwnd;
  int ssthresh;

  int not_acked;
  int dupAcks;
} State;

/**
 * Abstract base class for state stratigies
 */
class Strategy
{
public:
  /**
   * Init state parameters
   */
  void init(State *state)
  {
    state->cwnd = MSS;
    state->ssthresh = 64;
    state->dupAcks = 0;
  }

  virtual Strategy *newAck(State *state);         // on ack received
  virtual Strategy *timeout(State *state);        // on timeout
  virtual Strategy *duplicate(State *state);      // on duplicate ACK received
};

// class SlowStart : public Strategy
// {
// private:
//   static Strategy *inst;

// public:
//   static Strategy *getInst();
//   Strategy *newAck(State *state);
//   Strategy *timeout(State *state);
//   Strategy *duplicate(State *state);
// };

// class FastRecovery : public Strategy
// {
// private:
//   static Strategy *inst;

// public:
//   static Strategy *getInst();
//   Strategy *newAck(State *state);
//   Strategy *timeout(State *state);
//   Strategy *duplicate(State *state);
// };

// class CongestionAvoidance : public Strategy
// {
// private:
//   static Strategy *inst;

// public:
//   static Strategy *getInst();
//   Strategy *newAck(State *state);
//   Strategy *timeout(State *state);
//   Strategy *duplicate(State *state);
// };

// Strategy *SlowStart::getInst()
// {
//   if (inst == nullptr)
//     inst = new SlowStart();
//   return inst;
// }

// Strategy *SlowStart::newAck(State *state)
// {
//   state->cwnd += 1;
//   state->dupAcks = 0;
  
//   if(state->cwnd >= state->ssthresh){
//     init(state);
//     return CongestionAvoidance::getInst();
//   }

//   return this;
// }

// Strategy *SlowStart::timeout(State *state)
// {
//   state->ssthresh = state->cwnd / 2;
//   state->cwnd = 1;
//   state->dupAcks = 0;
//   return this;
// }

// Strategy *SlowStart::duplicate(State *state)
// {
//   state->dupAcks++;

//   if (state->dupAcks == 3)
//   {
//     state->ssthresh = state->cwnd / 2;
//     state->cwnd = state->ssthresh + 3 * 1;
//     return FastRecovery::getInst();
//   }

//   return this;
// }







// Strategy *FastRecovery::getInst()
// {
//   if (inst == nullptr)
//     inst = new FastRecovery();
//   return FastRecovery::inst;
// }

// Strategy *FastRecovery::newAck(State *state)
// {
//   state->cwnd = state->ssthresh;
//   state->dupAcks = 0;
//   return CongestionAvoidance::getInst();
// }

// Strategy *FastRecovery::timeout(State *state)
// {
//   state->ssthresh = state->cwnd / 2;
//   state->cwnd = 1;
//   state->dupAcks = 0;
//   return SlowStart::getInst();
// }

// Strategy *FastRecovery::duplicate(State *state)
// {
//   state->cwnd += 1;
//   return this;
// }






// Strategy *CongestionAvoidance::getInst()
// {
//   if (inst == nullptr)
//     inst = new CongestionAvoidance();
//   return CongestionAvoidance::inst;
// }

// Strategy *CongestionAvoidance::newAck(State *state)
// {
//   state->cwnd += 1;
//   state->dupAcks = 0;
//   return this;
// }

// Strategy *CongestionAvoidance::timeout(State *state)
// {
//   state->ssthresh = state->cwnd / 2;
//   state->cwnd = 1;
//   state->dupAcks = 0;
//   return SlowStart::getInst();
// }

// Strategy *CongestionAvoidance::duplicate(State *state)
// {
//   state->dupAcks++;

//   if (state->dupAcks == 3)
//   {
//     state->ssthresh = state->cwnd / 2;
//     state->cwnd = state->ssthresh + 3 * 1;
//     return FastRecovery::getInst();
//   }

//   return this;
// }