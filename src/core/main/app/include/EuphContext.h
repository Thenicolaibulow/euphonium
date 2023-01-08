#pragma once

#include <memory>

#include "CentralAudioBuffer.h"

#include "EventBus.h"
#include "StorageAccessor.h"
#include "BerryBind.h"

/**
 * @brief The main context of the application.
 * It holds pointers to a core set of utilities that are used through the entire system.
 * 
 * Notably:
 * - buffer -> Instance of CentralAudioBuffer
 * - storage -> Instance of the StorageAccessor, thats should be used to access the filesystem
 * - vm -> Instance of the VM, that should be used to run the scripts
 * - eventBus -> Instance of the EventBus, that should be used to communicate between the different parts of the system
*/
namespace euph {
// Used to control the state of playback. @TODO: Extend with loading state, error state, and such
struct PlaybackController {
  std::atomic<bool> isPaused = false;
  std::atomic<bool> requestPause = false;

  void pause() {
    this->requestPause = true;
  }

  void play() {
    this->isPaused = false;
  }
};

struct Context {
  std::shared_ptr<euph::StorageAccessor> storage;
  std::shared_ptr<berry::VmState> vm;
  std::shared_ptr<euph::EventBus> eventBus;
  std::shared_ptr<bell::CentralAudioBuffer> audioBuffer;
  std::shared_ptr<euph::PlaybackController> playbackController;


  /**
   * @brief Creates a context with the default utilities
   * 
   * @return std::shared_ptr<euph::Context> fresh context
   */
  static std::shared_ptr<euph::Context> create() {
    auto ctx = std::make_shared<euph::Context>();
    ctx->storage = std::make_shared<euph::StorageAccessor>();
    ctx->vm = std::make_shared<berry::VmState>();
    ctx->eventBus = std::make_shared<euph::EventBus>();
    ctx->audioBuffer = std::make_shared<bell::CentralAudioBuffer>(128);
    return ctx;
  }

  static std::shared_ptr<euph::Context> createWithBus(std::shared_ptr<euph::EventBus> bus) {
    auto ctx = std::make_shared<euph::Context>();
    ctx->storage = std::make_shared<euph::StorageAccessor>();
    ctx->vm = std::make_shared<berry::VmState>();
    ctx->audioBuffer = std::make_shared<bell::CentralAudioBuffer>(128);
    ctx->playbackController = std::make_shared<euph::PlaybackController>();
    ctx->eventBus = bus;

    #ifdef ESP_PLATFORM
    ctx->rootPath = "/fs";
    #endif
    return ctx;
  }

  // Path to the root of the filesystem
  std::string rootPath = "../src/core/fs";
};
}  // namespace euph
