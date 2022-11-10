//
// Created by Jiananyuan on 2022/10/19.
//

#include <vector>
#include <algorithm>
#include "config.h"

struct Segment {
    double slope;
    int start;

    Segment(double _slope, int _start) {
        slope = _slope;
        start = _start;
    }
};

std::vector<Segment> shrinkingcore_segmentation(std::vector<int> keys, std::vector<int> buf) {
  if (buf.size() != 0) {
    keys.insert(keys.end(), buf.begin(), buf.end());
    std::sort(keys.begin(), keys.end());
  }
  double sl_high = 1e9; // infinite
  double sl_low = 0;
  int origin_loc = 0;
  std::vector<Segment> segs;
  for (int i = 1; i < keys.size(); i += 1) {
    double k_up = i + config::ERROR;
    double k_low = i - config::ERROR;
    double max_bound = sl_high * keys[i];
    double min_bound = sl_low * keys[i];
    if (i >= min_bound && i <= max_bound) {
      sl_high = (k_up - origin_loc) / (keys[i] - keys[origin_loc]);
      sl_low = (k_low - origin_loc) / (keys[i] - keys[origin_loc]);
    }
    else {
      double slope = ((i - 1) - origin_loc) / (keys[i - 1] - keys[origin_loc]);
      segs.emplace_back(Segment(slope, keys[origin_loc]));
      origin_loc = i;
      sl_high = 1e9;
      sl_low = 0;
    }
  }
  return segs;
}
