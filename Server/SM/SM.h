#include "Strategies.h"

#define SM

#ifndef MSS
#define MSS 508
#endif

typedef struct
{
  int cwnd;
  int ssthresh;
  int seq_num;

  int not_acked;
  int dupAcks;
} State;

class SM
{
private:
  State *state;
  Strategy *strategy;

public:
  SM(); // Initial State
}

SM::SM()
{
  strategy = new SlowStart()
}

void SM::newAck()
{
}

void SM::timeout()
{
  ssthresh = cwnd / 2;
  cwnd = 1;
  dupAcks = 0;
}

void SM::duplicate()
{
  dupAcks++;

  if (dupAcks == 3)
  {
    status = FAST_RECOVERY;
    ssthresh = cwnd / 2;
    cwnd = ssthresh + 3 * MSS;
  }
}

void SM::threshExceeded()
{
  SM(); // reinitialize counters
  status = CONGESTION_AVOIDANCE;
}