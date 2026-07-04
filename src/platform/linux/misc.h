/**
 * @file src/platform/linux/misc.h
 * @brief Miscellaneous declarations for Linux.
 */
#pragma once

// standard includes
#include <unistd.h>
#include <vector>

// local includes
#include "src/utility.h"

#ifndef DOXYGEN
KITTY_USING_MOVE_T(file_t, int, -1, {
  if (el >= 0) {
    close(el);
  }
});
#else
/**
 * @brief Move-only wrapper for a POSIX file descriptor.
 */
class file_t;
#endif

/**
 * @brief Enumerates supported window system options.
 */
enum class window_system_e {
  NONE,  ///< No window system
  X11,  ///< X11
  WAYLAND,  ///< Wayland
};

extern window_system_e window_system;  ///< Window system.

namespace dyn {
  /**
   * @brief Generic GLX procedure pointer returned by the loader.
   */
  typedef void (*apiproc)(void);

  int load(void *handle, const std::vector<std::tuple<apiproc *, const char *>> &funcs, bool strict = true);
  void *handle(const std::vector<const char *> &libs);

}  // namespace dyn

#ifdef SUNSHINE_BUILD_DRM
namespace platf {
  /**
   * @brief Open a DRM card node and drop implicit DRM master, if any.
   *
   * Wraps `open(path, O_RDWR | O_CLOEXEC)` and probes the resulting fd with
   * `DRM_IOCTL_AUTH_MAGIC` to detect whether the kernel handed us master. If so, calls
   * `drmDropMaster` and re-verifies before returning. Only compiled when `SUNSHINE_BUILD_DRM`
   * is enabled.
   *
   * @param path Filesystem path to the DRM card node (e.g. `/dev/dri/card0`).
   * @return A non-master file descriptor on success, or `-1` on failure.
   */
  int open_drm_card_fd_non_master(const char *path);
}  // namespace platf
#endif
