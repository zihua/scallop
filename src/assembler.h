/*
Part of Scallop Transcript Assembler
(c) 2017 by  Mingfu Shao, Carl Kingsford, and Carnegie Mellon University.
See LICENSE for licensing.
*/

#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include <fstream>
#include <string>
#include "bundle_base.h"
#include "bundle.h"
#include "transcript.h"
#include "splice_graph.h"

using namespace std;

class assembler
{
public:
	assembler(const config &c);
	~assembler();

private:
	samFile *sfn;
	bam_hdr_t *hdr;
	bam1_t *b1t;
	bundle_base bb1;		// +
	bundle_base bb2;		// -
	vector<bundle_base> pool;

	int index;
	bool terminate;
	int qcnt;
	double qlen;
	vector<transcript> trsts;
	const config& cfg;

public:
	int assemble();
	assembler* solve(const config &c);
	bool operator>(const assembler &a);
	void improve(){}
	int write(const char* fname);

private:
	int process(int n);
	int assemble(const splice_graph &gr, const hyper_set &hs);
	int assign_RPKM();

	int compare(splice_graph &gr, const string &ref, const string &tex = "");
};

#endif
