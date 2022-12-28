class Packet {
  private:
    uint16_t len;
    uint32_t seqno;
    char content[500];

  public:
    Packet(uint16_t len, uint32_t seqno, char content[]);
}

Packet::Packet(uint16_t len, uint32_t seqno, char content[]) {
  this->len = len;
  this->seqno = seqno;
  this->content = content;
}