////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ASSERA_VALUE_CONVERSION
#define ASSERA_VALUE_CONVERSION

include "ir/include/value/ValueOps.td"
include "mlir/Dialect/StandardOps/IR/Ops.td"
include "mlir/Dialect/MemRef/IR/MemRefOps.td"

// These patterns are here to work around a bug with linalg.view operations that correspond to a single array element.
// The issue is that a store operation (either accv.StoreOp or (standard) StoreOp) with a (single-element) accv.OffsetOp
// eventually gets lowered to a store into a linalg.view, which fails when storing a single scalar value.
def : Pat<(accv_GetElementOp (accv_OffsetOp $source, $args)), (LoadOp $source, $args)>;
def : Pat<(accv_StoreOp $val, (accv_OffsetOp $source, $args), $indices), (MemRef_StoreOp $val, $source, $args)>;
def : Pat<(MemRef_StoreOp $val, (accv_OffsetOp $source, $args), $indices), (MemRef_StoreOp $val, $source, $args)>;

#endif // ASSERA_VALUE_CONVERSION
