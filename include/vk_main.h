#pragma once

#include <vk_exports.h>

namespace VK {
  EXPORT_VQS int mainRunTest(int numArgs, char** args);

  EXPORT_VQS int runWindow(VulkanAppPtr& pApp);
}
