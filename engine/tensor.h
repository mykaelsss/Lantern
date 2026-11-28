#pragma once
#include <cstddef>
#include <istream>
#include <stdexcept>
#include <vector>

template <class T> class Tensor {
public:
  T At(std::size_t row, std::size_t col) const {
    InRange(row, col);
    std::size_t idx = ComputeIdx(row, col);
    return vector_[idx];
  }
  void Set(T value, std::size_t row, std::size_t col) {
    InRange(row, col);
    std::size_t idx = ComputeIdx(row, col);
    vector_[idx] = value;
  }
  void Fill(std::istream &file) {
    auto size = vector_.size() * sizeof(T);
    file.read(reinterpret_cast<char *>(vector_.data()), size);
    if (!file) {
      throw std::runtime_error("unexpected end of file while reading tensor");
    }
  }
  std::size_t GetRows() const { return rows_; }
  std::size_t GetColumns() const { return cols_; }
  Tensor() : rows_(0), cols_(0), vector_(0, 0) {}
  Tensor(std::size_t rows, std::size_t cols)
      : rows_(rows), cols_(cols), vector_(rows * cols, 0) {}

private:
  std::size_t ComputeIdx(std::size_t row, std::size_t col) const {
    return (cols_ * row) + col;
  }
  void InRange(std::size_t row, std::size_t col) const {
    if (col >= cols_) {
      throw std::out_of_range("Column out of bounds");
    }
    if (row >= rows_) {
      throw std::out_of_range("Row out of bounds");
    }
  }
  std::size_t rows_;
  std::size_t cols_;
  std::vector<T> vector_;
};
