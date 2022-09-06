#include "vhash_group.hpp"

namespace KVDK_NAMESPACE {

bool VHashGroup::Create(StringView name) {
  auto acc = hpmap.lookup(name, hpmap.acquire_lock);
  if (acc.pointer() != nullptr) return false;
  VHash* vhash = vhb.NewVHash(name, kvb);
  acc.set_pointer(vhash);
  return true;
}

bool VHashGroup::Destroy(StringView name) {
  auto acc = hpmap.lookup(name, hpmap.acquire_lock);
  VHash* vhash = acc.pointer();
  if (vhash == nullptr) return false;
  acc.erase();
  vhb.Recycle(vhash);
  return true;
}

VHash* VHashGroup::Get(StringView name) {
  return hpmap.lookup(name, hpmap.lockless);
}

}  // namespace KVDK_NAMESPACE
