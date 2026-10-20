#include "random_vector.h"

#include <cstdlib>
#include <stdexcept>

RandomVector::RandomVector(int size, double max_val) {
  if (size < 0) {
    throw std::invalid_argument("RandomVector size must be non-negative");
  }

  vect.reserve(static_cast<std::size_t>(size));
  for (int i = 0; i < size; ++i) {
    const double unit = static_cast<double>(std::rand()) / RAND_MAX;
    vect.push_back(unit * max_val);
  }
}

void RandomVector::print() {
  for (std::size_t i = 0; i < vect.size(); ++i) {
    std::cout << vect[i];
    if (i + 1 != vect.size()) {
      std::cout << ' ';
    }
  }
  std::cout << std::endl;
}

double RandomVector::mean() {
  if (vect.empty()) {
    throw std::runtime_error("mean is undefined for an empty vector");
  }

  double sum = 0.0;
  for (const double value : vect) {
    sum += value;
  }
  return sum / static_cast<double>(vect.size());
}

double RandomVector::max() {
  if (vect.empty()) {
    throw std::runtime_error("maximum is undefined for an empty vector");
  }

  double result = vect[0];
  for (std::size_t i = 1; i < vect.size(); ++i) {
    if (vect[i] > result) {
      result = vect[i];
    }
  }
  return result;
}

double RandomVector::min() {
  if (vect.empty()) {
    throw std::runtime_error("minimum is undefined for an empty vector");
  }

  double result = vect[0];
  for (std::size_t i = 1; i < vect.size(); ++i) {
    if (vect[i] < result) {
      result = vect[i];
    }
  }
  return result;
}

void RandomVector::printHistogram(int bins) {
  if (bins <= 0) {
    throw std::invalid_argument("the number of histogram bins must be positive");
  }
  if (vect.empty()) {
    throw std::runtime_error("a histogram is undefined for an empty vector");
  }

  const double min_value = min();
  const double max_value = max();
  std::vector<int> counts(static_cast<std::size_t>(bins), 0);

  if (min_value == max_value) {
    counts[0] = static_cast<int>(vect.size());
  } else {
    const double width = (max_value - min_value) / bins;
    for (const double value : vect) {
      int index = static_cast<int>((value - min_value) / width);
      if (index == bins) {
        index = bins - 1;  // Include the maximum in the final bin.
      }
      ++counts[static_cast<std::size_t>(index)];
    }
  }

  int tallest_bin = 0;
  for (const int count : counts) {
    if (count > tallest_bin) {
      tallest_bin = count;
    }
  }

  for (int level = tallest_bin; level > 0; --level) {
    for (int i = 0; i < bins; ++i) {
      std::cout << (counts[static_cast<std::size_t>(i)] >= level ? "***" : "   ");
      if (i + 1 != bins) {
        std::cout << ' ';
      }
    }
    std::cout << std::endl;
  }
}

