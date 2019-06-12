/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * - Neither the name of prim nor the names of its contributors may be used to
 * endorse or promote products derived from this software without specific prior
 * written permission.
 *
 * See the NOTICE file distributed with this work for additional information
 * regarding copyright ownership.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef RND_RANDOM_H_
#define RND_RANDOM_H_

#include <prim/prim.h>

#include <random>

namespace rnd {

class Random {
 public:
  Random();
  explicit Random(u64 _seed);
  ~Random();
  void seed(u64 _seed);
  u64 nextU64();
  u64 nextU64(u64 _bits);
  u64 nextU64(u64 _min, u64 _max);
  f64 nextF64();
  f64 nextF64(f64 _min, f64 _max);  // _max is exclusive
  bool nextBool();

  // this shuffle the region of a container
  //  only works with RandomAccessIterators (e.g., vector, deque)
  template <typename Iterator>
  void shuffle(Iterator _first, Iterator _last);

  // this shuffle the entire container
  //  only works with RandomAccessIterators (e.g., vector, deque)
  template <typename Container>
  void shuffle(Container* _container);

  // this retrieves a random element from the container
  //  this does not remove the element
  template <typename Container>
  const typename Container::value_type& retrieve(const Container* _container);

  // this retrieves a random element from the container
  //  this removes the element from the container
  //  the container must support the 'erase' function
  template <typename Container>
  typename Container::value_type remove(Container* _container);

 private:
  std::mt19937_64 prng_;
  std::uniform_int_distribution<u64> intDist_;  // this defaults to [0,2^64-1]
  std::uniform_real_distribution<f64> realDist_;  // this defaults to [0,1)
};

}  // namespace rnd

#include "rnd/Random.tcc"

#endif  // RND_RANDOM_H_
