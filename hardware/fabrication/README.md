# Fabrication

The NAME PCB is a **single-sided through-hole board**, with copper on the bottom side only (`B.Cu`).

## Included files

- `../gerbers/NAME-B_Cu.gbr` — bottom copper
- `../gerbers/NAME-Edge_Cuts.gbr` — board outline
- `../gerbers/NAME-PTH.drl` — plated through-hole drill file
- `../gerbers/NAME-NPTH.drl` — non-plated through-hole drill file
- `../gerbers/NAME-job.gbrjob` — KiCad Gerber job description
- `BOM.csv` — bill of materials

No `F.Cu` Gerber is required because the design intentionally has no copper pattern on the top side.

## Status

The board design has been built, tested, and implemented in four capillary electrophoresis instruments. This folder contains the current fabrication outputs prepared for open release.

Before ordering boards from a manufacturer, users should still visually inspect the Gerbers with a Gerber viewer and confirm the manufacturer's interpretation of the single-sided stack-up and plated-hole requirements.
