#pragma leco tool

import jojo;
import jute;
import hai;
import print;

static auto next_idx(jute::view src) {
  auto c = src[0] | 0x20;
  if (c < 'a' || c > 'z') return 1;

  int i;
  for (i = 1; i < src.size(); i++) {
    auto c = src[i] | 0x20;
    if (c >= 'a' && c <= 'z') continue;
    if (c >= '0' && c <= '9') continue;
    if (c == '.') continue;
    break;
  }

  return i;
}

static auto split_tokens(jute::view src) {
  hai::chain<jute::view> tokens { 10240 };
  while (src.size()) {
    auto [t,r] = src.subview(next_idx(src));
    tokens.push_back(t);
    src = r;
  }
  return tokens;
}

int main() {
  auto src = jojo::read_cstr("Example.java");
  auto tokens = split_tokens(src);

  for (auto t : tokens) {
    putln(t);
  }
}
