# KiCad project

This directory contains the editable NAME hardware design in **KiCad 10.0** format.

Core project files:

- `NAME.kicad_pro` — KiCad project configuration
- `NAME.kicad_sch` — electrical schematic
- `NAME.kicad_pcb` — PCB layout

Project-specific libraries:

- `ADS1220_Custom.kicad_sym`
- `ADS1220_Custom.pretty/ADS1220_module.kicad_mod`
- `sym-lib-table`
- `fp-lib-table`

The custom libraries use `${KIPRJMOD}` references and therefore travel with the project. Standard 3D models use `${KICAD10_3DMODEL_DIR}` and are expected to be supplied by a normal KiCad 10 installation.

Local KiCad preference, history, backup, lock, and autosave files are intentionally excluded from version control.

## Hardware license

Unless explicitly stated otherwise, the hardware design files in this directory are licensed under CERN-OHL-S-2.0. See the repository root `LICENSE-HARDWARE` file.
