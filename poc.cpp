#pragma leco tool

import jojo;
import jute;
import hai;
import hashley;
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
  auto src = jojo::read_cstr("/dev/stdin");
  auto tokens = split_tokens(src);

  hashley::niamh dedup { 127 };
  hai::varray<jute::view> imports { 10240 };

  bool first = true;
  for (auto t : tokens) {
    auto [l,r] = t.rsplit('.');
    if (l.size() == 0) continue;
    if (first) {
      put("package ");
      put(l);
      putln(';');
      putln();
      first = false;
    } else {
      if (t.starts_with("java.lang.")) continue;

      auto & d = dedup[t];
      if (d) continue;
      d = 1;

      imports.push_back_doubling(t);
    }
  }
  for (auto i = 0; i < imports.size(); i++) {
    auto & ii = imports[i];
    for (auto j = i + 1; j < imports.size(); j++) {
      auto & jj = imports[j];
      if (ii < jj) continue;
      auto tmp = ii;
      ii = jj;
      jj = tmp;
    }
  }

  for (auto i : imports) putln("import ", i, ";");
  putln();

  for (auto t : tokens) {
    auto [l,r] = t.rsplit('.');
    if (l.size() == 0) {
      put(t);
    } else {
      put(r);
    }
  }
}
