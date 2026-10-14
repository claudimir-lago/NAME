# Gerber and drill files

This directory contains the fabrication outputs for the NAME PCB.

NAME is intentionally designed as a **single-sided PCB**, with all copper routing on the bottom side (`B.Cu`). Therefore no `F.Cu` Gerber is included or required.

## Files

- `NAME-B_Cu.gbr` — bottom copper layer
- `NAME-Edge_Cuts.gbr` — board profile
- `NAME-PTH.drl` — plated through-hole drilling
- `NAME-NPTH.drl` — non-plated drilling
- `NAME-job.gbrjob` — KiCad Gerber job file

The board outline file contains only the board profile.

Users should verify the files in a Gerber viewer before fabrication. Depending on the board house, a nominally two-sided FR4 process may still be used while the top copper pattern remains absent.
