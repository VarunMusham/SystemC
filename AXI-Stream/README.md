# AXI4-Stream LT (Very Basic Example)

This folder contains a minimal AXI4-Stream-style example using SystemC TLM (loosely timed).

## Files

- `axi_payload.h`: shared packet type
- `axi_master.h`: master module
- `axi_slave.h`: slave module
- `main.cpp`: one simple testbench
- `Makefile`: build/run commands

## Build and run

```powershell
cd d:\Programming\SystemC\AXI-Stream
make clean
make all
make run
```

## Expected output

```text
Sending data...
Received 2 packets
Test PASSED
```

## Minimal usage

```cpp
AXIPayload pkt(64);
pkt.data[0] = 0x12;
pkt.last = false;
master->send(pkt);
```

## Notes

- Keep using `make run` from this folder.
- `sim.exe` is generated automatically and is ignored by git.

## Extension Ideas

1. **Add Flow Control**: Implement READY signal
2. **Add Backpressure**: Block transfers when slave is busy
3. **FIFO Buffer**: Add buffering between master and slave
4. **Error Handling**: Add error generation/detection
5. **Statistics**: Track latency, throughput, errors
6. **Multiple Streams**: Demultiplexer/Multiplexer for multiple data channels

## Troubleshooting

### Compilation Issues

**Problem**: `undefined reference to 'sc_main'`
- **Solution**: Ensure you have exactly one sc_main() in your project

**Problem**: `cannot find systemc headers`
- **Solution**: Check SYSTEMC_HOME path in Makefile matches your installation

### Runtime Issues

**Problem**: `No transactions received`
- **Solution**: Check that master is properly connected; verify reset sequence

**Problem**: `Simulation hangs`
- **Solution**: Ensure sc_stop() is called; check for infinite loops in send_data()

## Performance Tips

1. Use LT model for quick exploration (current implementation)
2. Switch to AT (Approximate Timed) for better accuracy if needed
3. Disable waveform tracing for faster simulation
4. Use sc_pause() for debugging specific cycles

## References

- [SystemC TLM Documentation](http://www.systemc.org/)
- [AMBA AXI4-Stream Specification](https://developer.arm.com/)
- [TLM Modeling Examples](https://systemc.org/download/standards/)

## License

This implementation is provided as-is for educational and development purposes.

## Support

For questions or issues:
1. Review the example files
2. Check SystemC documentation
3. Verify all connections in your testbench
4. Use sc_report_handler for debugging

---

**Last Updated**: 2026  
**SystemC Version**: 2.3.3+  
**TLM Version**: 2.0
