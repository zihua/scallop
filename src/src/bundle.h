#ifndef __BUNDLE_H__
#define __BUNDLE_H__

#include <stdint.h>
#include <cstring>
#include <string>
#include <vector>

#include "hit.h"
#include "sam.h"
#include "common.h"
#include "bridge.h"
#include "boundary.h"
#include "region.h"
#include "sgraph.h"

using namespace std;

class bundle
{
public:
	bundle();
	~bundle();

public:
	int32_t tid;					// chromosome ID
	string chrm;					// chromosome name
	int32_t lpos;					// the leftmost boundary on reference
	int32_t rpos;					// the rightmost boundary on reference

	vector<hit> hits;				// hits
	imap_t imap;					// interval map
	vector<bridge> bridges;			// splice bridges
	vector<boundary> boundaries;	// all types of boundaries
	vector<region> regions;			// regions

public:
	int build_splice_graph(sgraph &sg);
	int clear();
	int print();
	int solve();

public:
	// add hit to hits
	int add_hit(bam_hdr_t *h, bam1_t *b);

	// check whether hits are sorted
	int check_left_ascending();
	int check_right_ascending();

	// build interval map
	int build_interval_map();

	// remove these intervals starting at a LEFT_BOUNDARY
	int remove_left_boundary_intervals();

	// binary search for a specific given starting point, return count
	int locate_hits(int32_t p, int &li);

	// infer boundaries
	int infer_bridges();
	int infer_left_boundaries();
	int infer_right_boundaries();
	int add_start_boundary();
	int add_end_boundary();

	// build regions
	int build_regions();
};

#endif
