# Integration with Zones

NAME and Zones are independent projects with complementary roles.

NAME provides the measured electrophoretic current as a function of time, **I(t)**. The hardware itself does not need to calculate electrical charge. Charge-domain processing is performed in software by integrating the recorded current signal.

[Zones](https://github.com/claudimir-lago/Zones) can use electrophoretic-current data as part of its data-processing workflow, including charge-domain analysis.

A precise exchange format, synchronization requirements, sign conventions, and worked examples will be documented here as the public release is completed.
