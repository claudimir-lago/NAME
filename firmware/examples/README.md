# NAME Arduino examples

The examples in this directory are intentionally small and focus only on NAME
current acquisition.

- `01_basic_readout/` — simplest blocking ADS1220 readout and serial CSV output.
- `02_nonblocking_readout/` — DRDY-interrupt approach extracted from the
  minimalistiCE implementation.

Both examples use the bundled `ADS1220_WE_SoftSPI` library located in
`../libraries/ADS1220_WE_SoftSPI/`.

The pin assignment in the examples reflects the Arduino UNO R4 Minima used in
the minimalistiCE implementation. Because communication is software SPI, the
pins can be reassigned to suit another controller.

The examples use the current conversion implemented in the working
minimalistiCE firmware:

```cpp
constexpr float NAME_NA_PER_MV = 200.0f;
```

This makes the circuit-specific conversion explicit instead of leaving the
factor as an unexplained numeric constant.
