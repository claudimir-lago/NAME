# Changelog

## Unreleased

## [1.0.0] - 2026-10-14

### Added
- First public release of NAME — Nanoampere Meter for Electrophoresis.
- KiCad 10.0 schematic and PCB source files, including project-specific ADS1220 symbol and footprint libraries.
- Fabrication outputs for the single-sided `B.Cu` PCB, plated/non-plated drill files, Gerber job metadata, and BOM.
- PDF export of the electrical schematic and photograph of an assembled NAME board.
- Arduino blocking and non-blocking acquisition examples.
- Bundled `ADS1220_WE_SoftSPI` library with its MIT license and attribution.
- Documentation covering operating principle, the nominal `200 nA/mV` conversion, differential zero adjustment, optional calibration, connector pinout, integration, safety, and frequency response.
- Citation metadata for Claudimir Lucio do Lago and Ivan Verlangieri.

### Validated
- Hardware has been built, tested, and implemented in four CE instruments.
- Both Arduino examples were compiled successfully before release.

## v0.9

- Added frequency-response and filtering documentation to `docs/principle-of-operation.md`.
- Documented the nominal 3.18 kHz pole from the 5 kOhm Thevenin resistance and 10 nF capacitor.
- Documented the additional differential-input filtering provided by the 100 nF capacitor without assigning an unsupported exact cutoff frequency.
- Documented the additional bandwidth limitation from `ADS1220_50HZ_60HZ` digital filtering.
- Clarified why suppression of fast current fluctuations is compatible with NAME's intended measurement of effective electrophoretic current and accumulated charge.
- Updated the documentation roadmap to distinguish completed initial documentation from characterization still to be added.
## v0.8

- Added the complete J1, J2, and J3 connector pinout.
- Documented J1 connection to the low-voltage CE electrode and cable shield.
- Documented the 3–5 V J2 power input.
- Documented the J3 SoftSPI interface and the currently unused CLK pin.
- Added a minimal installation and zero-adjustment sequence in `docs/interfacing.md`.

## v0.7

- Added a documented derivation of the nominal NAME conversion factor (`200 nA/mV`) from the 5 kOhm Thevenin equivalent of R2 and R3.
- Documented the ADS1220 differential-zero adjustment using RV1, R4, and R5.
- Added an explicit optional firmware calibration factor.
- Documented both the minimalistiCE conversion approach and the calibrated Mark44 scaling approach.
- Updated the basic and non-blocking Arduino examples accordingly.

## [0.6.0] - 2026-10-14

### Added
- Bundled `ADS1220_WE_SoftSPI`, the software-SPI ADS1220 interface used by the reference NAME implementation.
- Library-specific MIT license and attribution to the original `ADS1220_WE` project by Wolfgang (Wolle) Ewald.
- Arduino library metadata and installation notes.
- `01_basic_readout`, a minimal blocking NAME acquisition example.
- `02_nonblocking_readout`, a simplified DRDY-interrupt example extracted from the NAME acquisition strategy used in minimalistiCE.

### Changed
- Made the deployed current-conversion factor explicit as `NAME_NA_PER_MV = 200.0f` in the examples.
- Documented the Arduino UNO R4 Minima pin assignment used by the minimalistiCE implementation while emphasizing that SoftSPI permits pin reassignment.
- Corrected the main README fabrication status to reflect the intentional single-sided `B.Cu`-only PCB.
- Expanded licensing documentation to distinguish NAME-specific GPL code from the bundled MIT-licensed library.

## [0.5] - 2026-10-14

### Changed
- Clarified that the NAME PCB is intentionally single-sided, with copper on `B.Cu` only.
- Removed the previous assumption that `F.Cu` was missing from the fabrication package.
- Marked the current Gerber/drill set as the intended fabrication output for the single-sided design.
- Updated fabrication documentation to explain the stack-up and plated-hole interpretation.

## [0.4.0] - 2026-10-14

- Added the first KiCad-generated fabrication outputs: bottom copper, corrected board outline, plated and non-plated drill files, and Gerber job metadata.
- Added the KiCad-exported bill of materials (BOM).
- Documented that the current fabrication set is still missing `F.Cu`; this layer is required for the top annular rings of plated through-hole pads even though routing is confined to `B.Cu`.
- Marked the fabrication package as pending rather than manufacturing-ready until the front-copper Gerber and matching regenerated `.gbrjob` are added.

## [0.3.0] - 2026-10-14

- Clarified that NAME is advanced working hardware already implemented in four CE instruments.
- Added project-status documentation.
- Added initial Zones-integration and electrical-safety documentation.
- Expanded fabrication-release guidance.
- Defined the scope of the first firmware example without inventing unverified acquisition parameters.

All notable changes to NAME will be documented in this file.
