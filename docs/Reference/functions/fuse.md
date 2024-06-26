[//]: # (Project: Assera)
[//]: # (Version: v1.2)

# Assera v1.2 Reference

## `assera.fuse(schedules[, *args, partial])`
The `fuse` operation combines multiple iteration spaces into a single "fused" iteration space. The fused iteration space represents the union of the work in the original spaces.

In cases where it doesn't make sense to fuse all of the iteration space dimensions, we can choose to fuse a prefix of the dimensions and leave the rest unfused.

## Arguments

argument | description | type/default
--- | --- | ---
`schedules` | If performing partial fusing, this is a tuple of the schedules to fuse. If performing full fusing, this contains the first schedule to fuse, while `args` will contain the subsequent schedules.
`*args` | Optional variable arguments containing subsequent schedules to fuse | variable `Schedule` arguments
`partial` | The number of dimensions to fuse. If not specified, all dimensions will be fused | non-negative integer

## Returns
Instance of `FusedSchedule`

## Examples

Full fusing of same-shaped iteration spaces:

```python
# Fuse all dimensions of schedule0 and schedule1
schedule = acc.fuse(schedule0, schedule1)
```

Partial iteration space fusing:

```python
# Fuse the first two dimensions of schedule0 and schedule1
schedule = acc.fuse((schedule0, schedule1), partial=2)
```


<div style="page-break-after: always;"></div>


