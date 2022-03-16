#ifndef MEMORY_CLASS_H
#define MEMORY_CLASS_H

#include <limits>

#include "block.h"

// CACHE ACCESS TYPE
#define LOAD 0
#define RFO 1
#define PREFETCH 2
#define WRITEBACK 3
#define TRANSLATION 4
#define NUM_TYPES 5

class MemoryRequestConsumer
{
public:
  virtual bool add_rq(const PACKET &packet) = 0;
  virtual bool add_wq(const PACKET &packet) = 0;
  virtual bool add_pq(const PACKET &packet) = 0;
  virtual uint32_t get_occupancy(uint8_t queue_type, uint64_t address) = 0;
  virtual uint32_t get_size(uint8_t queue_type, uint64_t address) = 0;

  explicit MemoryRequestConsumer() {}
};

class MemoryRequestProducer
{
public:
  MemoryRequestConsumer* lower_level;
  virtual void return_data(const PACKET& packet) = 0;

protected:
  MemoryRequestProducer() {}
  explicit MemoryRequestProducer(MemoryRequestConsumer* ll) : lower_level(ll) {}
};

#endif
