#ifndef RBX_METRICS_HPP
#define RBX_METRICS_HPP

#include "internal_threads.hpp"

#include "gc/root.hpp"

#include "util/timer.hpp"

#include <stdint.h>

#include <string>
#include <vector>

namespace rubinius {
  class VM;
  class State;
  class Tuple;
  class SharedState;

  namespace metrics {
    typedef uint64_t metric;

    struct CodeDBMetrics {
      metric load_us;

      CodeDBMetrics() {
        load_us = 0;
      }

      void add(CodeDBMetrics& data) {
        load_us += data.load_us;
      }
    };

    struct ConsoleMetrics {
      metric requests_received;
      metric responses_sent;

      ConsoleMetrics() {
        requests_received = 0;
        responses_sent = 0;
      }

      void add(ConsoleMetrics& data) {
        requests_received += data.requests_received;
        responses_sent += data.responses_sent;
      }
    };

    struct GCMetrics {
      metric young_count;
      metric young_ms;
      metric immix_count;
      metric immix_stop_ms;
      metric immix_concurrent_ms;
      metric large_count;
      metric large_sweep_us;
      metric objects_queued;
      metric objects_finalized;

      GCMetrics() {
        young_count = 0;
        young_ms = 0;
        immix_count = 0;
        immix_stop_ms = 0;
        immix_concurrent_ms = 0;
        large_count = 0;
        large_sweep_us = 0;
        objects_queued = 0;
        objects_finalized = 0;
      }

      void add(GCMetrics& data) {
        young_count += data.young_count;
        young_ms += data.young_ms;
        immix_count += data.immix_count;
        immix_stop_ms += data.immix_stop_ms;
        immix_concurrent_ms += data.immix_concurrent_ms;
        large_count += data.large_count;
        large_sweep_us += data.large_sweep_us;
        objects_queued += data.objects_queued;
        objects_finalized += data.objects_finalized;
      }
    };

    struct JITMetrics {
      metric methods_queued;
      metric methods_compiled;
      metric methods_failed;
      metric compile_time_us;
      metric uncommon_exits;
      metric inlined_accessors;
      metric inlined_methods;
      metric inlined_blocks;
      metric inlined_primitives;
      metric inlined_ffi;

      JITMetrics() {
        methods_queued = 0;
        methods_compiled = 0;
        methods_failed = 0;
        compile_time_us = 0;
        uncommon_exits = 0;
        inlined_accessors = 0;
        inlined_methods = 0;
        inlined_blocks = 0;
        inlined_primitives = 0;
        inlined_ffi = 0;
      }

      void add(JITMetrics& data) {
        methods_queued += data.methods_queued;
        methods_compiled += data.methods_compiled;
        methods_failed += data.methods_failed;
        compile_time_us += data.compile_time_us;
        uncommon_exits += data.uncommon_exits;
        inlined_accessors += data.inlined_accessors;
        inlined_methods += data.inlined_methods;
        inlined_blocks += data.inlined_blocks;
        inlined_primitives += data.inlined_primitives;
        inlined_ffi += data.inlined_ffi;
      }
    };

    struct LockMetrics {
      metric stop_the_world_ns;

      LockMetrics() {
        stop_the_world_ns = 0;
      }

      void add(LockMetrics& data) {
        stop_the_world_ns += data.stop_the_world_ns;
      }
    };

    struct MachineMetrics {
      metric inline_cache_resets;
      metric methods_invoked;
      metric blocks_invoked;

      MachineMetrics() {
        inline_cache_resets = 0;
        methods_invoked = 0;
        blocks_invoked = 0;
      }

      void add(MachineMetrics& data) {
        inline_cache_resets += data.inline_cache_resets;
        methods_invoked += data.methods_invoked;
        blocks_invoked += data.blocks_invoked;
      }
    };

    struct MemoryMetrics {
      metric young_bytes;
      metric young_objects;
      metric young_occupancy;
      metric immix_bytes;
      metric immix_objects;
      metric immix_chunks;
      metric large_bytes;
      metric large_objects;
      metric symbols;
      metric symbols_bytes;
      metric code_bytes;
      metric jit_bytes;
      metric promoted_bytes;
      metric promoted_objects;
      metric slab_refills;
      metric slab_refills_fails;
      metric data_objects;
      metric capi_handles;
      metric inflated_headers;

      MemoryMetrics() {
        young_bytes = 0;
        young_objects = 0;
        young_occupancy = 0;
        immix_bytes = 0;
        immix_objects = 0;
        immix_chunks = 0;
        large_bytes = 0;
        large_objects = 0;
        symbols = 0;
        symbols_bytes = 0;
        code_bytes = 0;
        jit_bytes = 0;
        promoted_bytes = 0;
        promoted_objects = 0;
        slab_refills = 0;
        slab_refills_fails = 0;
        data_objects = 0;
        capi_handles = 0;
        inflated_headers = 0;
      }

      void add(MemoryMetrics& data) {
        young_bytes += data.young_bytes;
        young_objects += data.young_objects;
        young_occupancy += data.young_occupancy;
        immix_bytes += data.immix_bytes;
        immix_objects += data.immix_objects;
        immix_chunks += data.immix_chunks;
        large_bytes += data.large_bytes;
        large_objects += data.large_objects;
        symbols += data.symbols;
        symbols_bytes += data.symbols_bytes;
        code_bytes += data.code_bytes;
        jit_bytes += data.jit_bytes;
        promoted_bytes += data.promoted_bytes;
        promoted_objects += data.promoted_objects;
        slab_refills += data.slab_refills;
        slab_refills_fails += data.slab_refills_fails;
        data_objects += data.data_objects;
        capi_handles += data.capi_handles;
        capi_handles += data.capi_handles;
        inflated_headers += data.inflated_headers;
      }
    };

    struct SystemMetrics {
      metric read_bytes;
      metric write_bytes;
      metric signals_received;
      metric signals_processed;
      metric threads_created;
      metric threads_destroyed;

      SystemMetrics() {
        read_bytes = 0;
        write_bytes = 0;
        signals_received = 0;
        signals_processed = 0;
        threads_created = 0;
        threads_destroyed = 0;
      }

      void add(SystemMetrics& data) {
        read_bytes += data.read_bytes;
        write_bytes += data.write_bytes;
        signals_received += data.signals_received;
        signals_processed += data.signals_processed;
        threads_created += data.threads_created;
        threads_destroyed += data.threads_destroyed;
      }
    };

    struct MetricsData {
      CodeDBMetrics codedb;
      ConsoleMetrics console;
      GCMetrics gc;
      JITMetrics jit;
      LockMetrics lock;
      MachineMetrics machine;
      MemoryMetrics memory;
      SystemMetrics system;

      MetricsData()
        : codedb()
        , console()
        , gc()
        , jit()
        , lock()
        , machine()
        , memory()
        , system()
      { }

      void add(MetricsData& data) {
        codedb.add(data.codedb);
        console.add(data.console);
        gc.add(data.gc);
        jit.add(data.jit);
        lock.add(data.lock);
        machine.add(data.machine);
        memory.add(data.memory);
        system.add(data.system);
      }
    };

    typedef std::pair<std::string, metric&> MetricsItem;
    typedef std::vector<MetricsItem*> MetricsMap;

    class MetricsEmitter {
    public:
      MetricsEmitter() { }
      virtual ~MetricsEmitter() { };

      virtual void send_metrics() = 0;
      virtual void initialize() = 0;
      virtual void cleanup() = 0;
      virtual void reinit() = 0;
    };

    class FileEmitter : public MetricsEmitter {
      MetricsMap& metrics_map_;
      std::string path_;
      int fd_;

    public:
      FileEmitter(MetricsMap& map, std::string path);
      virtual ~FileEmitter();

      void send_metrics();
      void initialize();
      void cleanup();
      void reinit();
    };

    class StatsDEmitter : public MetricsEmitter {
      MetricsMap& metrics_map_;
      std::string host_;
      std::string port_;
      std::string prefix_;
      int socket_fd_;

    public:
      StatsDEmitter(MetricsMap& map, std::string server, std::string prefix);
      virtual ~StatsDEmitter();

      void send_metrics();
      void initialize();
      void cleanup();
      void reinit();
    };

    class Metrics : public InternalThread {
      bool enabled_;

      TypedRoot<Tuple*> values_;

      int interval_;
      utilities::timer::Timer* timer_;
      utilities::thread::Mutex metrics_lock_;

      MetricsData metrics_data_;
      MetricsData metrics_history_;

      MetricsMap metrics_map_;

      MetricsEmitter* emitter_;

    public:
      Metrics(STATE);
      virtual ~Metrics();

      void map_metrics();

      void add_historical_metrics(MetricsData& metrics);

      void init_ruby_metrics(STATE);
      void update_ruby_values(STATE);

      void disable(STATE) {
        enabled_ = false;
      }

      void initialize(STATE);
      void run(STATE);
      void wakeup(STATE);
      void after_fork_child(STATE);
    };
  }
}

#endif
