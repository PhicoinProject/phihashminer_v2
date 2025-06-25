#pragma once

#include <stdint.h>
#include <string>

// blocks before changing the random program
#define PHIHASH_PERIOD          3
// lanes that work together calculating a hash
#define PHIHASH_LANES           16
// uint32 registers per lane
#define PHIHASH_REGS            32
// uint32 loads from the DAG per lane
#define PHIHASH_DAG_LOADS       4
// size of the cached portion of the DAG
#define PHIHASH_CACHE_BYTES     (16*1024)
// DAG accesses, also the number of loops executed
#define PHIHASH_CNT_DAG         64
// random cache accesses per loop
#define PHIHASH_CNT_CACHE       11
// random math instructions per loop
#define PHIHASH_CNT_MATH        18

#define EPOCH_LENGTH            30000

class PhiHash
{
public:
	typedef enum {
		KERNEL_CUDA,
		KERNEL_CL
	} kernel_t;

	static std::string getKern(uint64_t seed, kernel_t kern);
private:
    static std::string math(std::string d, std::string a, std::string b, uint32_t r);
    static std::string merge(std::string a, std::string b, uint32_t r);

    static uint32_t fnv1a(uint32_t &h, uint32_t d);
    // KISS99 is simple, fast, and passes the TestU01 suite
    // https://en.wikipedia.org/wiki/KISS_(algorithm)
    // http://www.cse.yorku.ca/~oz/marsaglia-rng.html
    typedef struct {
        uint32_t z, w, jsr, jcong;
    } kiss99_t;
    static uint32_t kiss99(kiss99_t &st);
};