; ModuleID = 'src/main.cpp'
source_filename = "src/main.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@__undef = external local_unnamed_addr global i64, align 8

; Function Attrs: mustprogress uwtable
define dso_local void @_Z17__retain_pointersv() local_unnamed_addr #0 {
entry:
  store i64 0, ptr @__undef, align 8, !tbaa !5
  %call = tail call i64 @__warbird_retain_value(i64 noundef 0)
  %call1 = tail call i64 @__warbird_stub(ptr noundef null, ptr noundef null)
  ret void
}

declare i64 @__warbird_retain_value(i64 noundef) local_unnamed_addr #1

declare i64 @__warbird_stub(ptr noundef, ptr noundef) local_unnamed_addr #1

; Function Attrs: alwaysinline mustprogress uwtable
define dso_local i64 @__warbird_vm(ptr noalias noundef %memory, ptr noalias noundef %vsp, i64 noundef %arg0, i64 noundef %arg1, i64 noundef %arg2, i64 noundef %arg3) local_unnamed_addr #2 {
entry:
  %vsp.addr = alloca ptr, align 8
  %context = alloca [56 x i64], align 16
  store volatile ptr %vsp, ptr %vsp.addr, align 8, !tbaa !9
  call void @llvm.lifetime.start.p0(i64 448, ptr nonnull %context) #9
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(448) %context, i8 0, i64 448, i1 false)
  %arrayidx = getelementptr inbounds nuw i8, ptr %context, i64 64
  store i64 %arg0, ptr %arrayidx, align 16, !tbaa !5
  %arrayidx1 = getelementptr inbounds nuw i8, ptr %context, i64 40
  store i64 %arg1, ptr %arrayidx1, align 8, !tbaa !5
  %arrayidx2 = getelementptr inbounds nuw i8, ptr %context, i64 312
  store i64 %arg2, ptr %arrayidx2, align 8, !tbaa !5
  %arrayidx3 = getelementptr inbounds nuw i8, ptr %context, i64 144
  store i64 %arg3, ptr %arrayidx3, align 16, !tbaa !5
  %vsp.addr.0.vsp.addr.0.vsp.addr.0.vsp.addr.0. = load volatile ptr, ptr %vsp.addr, align 8, !tbaa !9
  %0 = ptrtoint ptr %vsp.addr.0.vsp.addr.0.vsp.addr.0.vsp.addr.0. to i64
  %arrayidx4 = getelementptr inbounds nuw i8, ptr %context, i64 392
  store i64 %0, ptr %arrayidx4, align 8, !tbaa !5
  %vsp.addr.0.vsp.addr.0.vsp.addr.0.vsp.addr.0.7 = load volatile ptr, ptr %vsp.addr, align 8, !tbaa !9
  %1 = ptrtoint ptr %vsp.addr.0.vsp.addr.0.vsp.addr.0.vsp.addr.0.7 to i64
  %arrayidx5 = getelementptr inbounds nuw i8, ptr %context, i64 120
  store i64 %1, ptr %arrayidx5, align 8, !tbaa !5
  %call = call i64 @__warbird_stub(ptr noundef nonnull %context, ptr noundef %memory)
  %2 = load i64, ptr %arrayidx4, align 8, !tbaa !5
  call void @llvm.lifetime.end.p0(i64 448, ptr nonnull %context) #9
  ret i64 %2
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #3

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #4

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #3

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define dso_local zeroext i8 @__remill_read_memory_8(ptr noalias nocapture noundef readonly %memory, i64 noundef %addr) local_unnamed_addr #5 {
entry:
  %arrayidx = getelementptr inbounds nuw i8, ptr %memory, i64 %addr
  %v.0.copyload = load i8, ptr %arrayidx, align 1
  ret i8 %v.0.copyload
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define dso_local zeroext i16 @__remill_read_memory_16(ptr noalias nocapture noundef readonly %memory, i64 noundef %addr) local_unnamed_addr #5 {
entry:
  %arrayidx = getelementptr inbounds nuw i8, ptr %memory, i64 %addr
  %v.0.copyload = load i16, ptr %arrayidx, align 1
  ret i16 %v.0.copyload
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define dso_local i32 @__remill_read_memory_32(ptr noalias nocapture noundef readonly %memory, i64 noundef %addr) local_unnamed_addr #5 {
entry:
  %arrayidx = getelementptr inbounds nuw i8, ptr %memory, i64 %addr
  %v.0.copyload = load i32, ptr %arrayidx, align 1
  ret i32 %v.0.copyload
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define dso_local i64 @__remill_read_memory_64(ptr noalias nocapture noundef readonly %memory, i64 noundef %addr) local_unnamed_addr #5 {
entry:
  %arrayidx = getelementptr inbounds nuw i8, ptr %memory, i64 %addr
  %v.0.copyload = load i64, ptr %arrayidx, align 1
  ret i64 %v.0.copyload
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write) uwtable
define dso_local noundef ptr @__remill_write_memory_8(ptr noalias noundef returned writeonly %memory, i64 noundef %addr, i8 noundef zeroext %value) local_unnamed_addr #6 {
entry:
  %arrayidx = getelementptr inbounds nuw i8, ptr %memory, i64 %addr
  store i8 %value, ptr %arrayidx, align 1
  ret ptr %memory
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write) uwtable
define dso_local noundef ptr @__remill_write_memory_16(ptr noalias noundef returned writeonly %memory, i64 noundef %addr, i16 noundef zeroext %value) local_unnamed_addr #6 {
entry:
  %arrayidx = getelementptr inbounds nuw i8, ptr %memory, i64 %addr
  store i16 %value, ptr %arrayidx, align 1
  ret ptr %memory
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write) uwtable
define dso_local noundef ptr @__remill_write_memory_32(ptr noalias noundef returned writeonly %memory, i64 noundef %addr, i32 noundef %value) local_unnamed_addr #6 {
entry:
  %arrayidx = getelementptr inbounds nuw i8, ptr %memory, i64 %addr
  store i32 %value, ptr %arrayidx, align 1
  ret ptr %memory
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write) uwtable
define dso_local noundef ptr @__remill_write_memory_64(ptr noalias noundef returned writeonly %memory, i64 noundef %addr, i64 noundef %value) local_unnamed_addr #6 {
entry:
  %arrayidx = getelementptr inbounds nuw i8, ptr %memory, i64 %addr
  store i64 %value, ptr %arrayidx, align 1
  ret ptr %memory
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef ptr @__remill_barrier_load_load(ptr noalias noundef readnone returned %memory) local_unnamed_addr #7 {
entry:
  ret ptr %memory
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef ptr @__remill_barrier_load_store(ptr noalias noundef readnone returned %memory) local_unnamed_addr #7 {
entry:
  ret ptr %memory
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef ptr @__remill_barrier_store_load(ptr noalias noundef readnone returned %memory) local_unnamed_addr #7 {
entry:
  ret ptr %memory
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef ptr @__remill_barrier_store_store(ptr noalias noundef readnone returned %memory) local_unnamed_addr #7 {
entry:
  ret ptr %memory
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef ptr @__remill_atomic_begin(ptr noalias noundef readnone returned %memory) local_unnamed_addr #7 {
entry:
  ret ptr %memory
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef ptr @__remill_atomic_end(ptr noalias noundef readnone returned %memory) local_unnamed_addr #7 {
entry:
  ret ptr %memory
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef ptr @__remill_delay_slot_begin(ptr noalias noundef readnone returned %memory) local_unnamed_addr #7 {
entry:
  ret ptr %memory
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef ptr @__remill_delay_slot_end(ptr noalias noundef readnone returned %memory) local_unnamed_addr #7 {
entry:
  ret ptr %memory
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef ptr @__remill_missing_block(ptr noalias nocapture noundef readnone %0, i64 noundef %1, ptr noalias noundef readnone returned %memory) local_unnamed_addr #7 {
entry:
  ret ptr %memory
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef ptr @__remill_function_return(ptr noalias nocapture noundef readnone %0, i64 noundef %1, ptr noalias noundef readnone returned %memory) local_unnamed_addr #7 {
entry:
  ret ptr %memory
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef ptr @__remill_jump(ptr noalias nocapture noundef readnone %0, i64 noundef %1, ptr noalias noundef readnone returned %memory) local_unnamed_addr #7 {
entry:
  ret ptr %memory
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i8 @__remill_undefined_8() local_unnamed_addr #7 {
entry:
  ret i8 0
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i16 @__remill_undefined_16() local_unnamed_addr #7 {
entry:
  ret i16 0
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef i32 @__remill_undefined_32() local_unnamed_addr #7 {
entry:
  ret i32 0
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef i64 @__remill_undefined_64() local_unnamed_addr #7 {
entry:
  ret i64 0
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nounwind willreturn memory(argmem: readwrite) uwtable
define dso_local noundef ptr @__remill_compare_exchange_memory_32(ptr noalias noundef returned %memory, i64 noundef %addr, ptr nocapture noundef nonnull align 4 dereferenceable(4) %expected, i32 noundef %desired) local_unnamed_addr #8 {
entry:
  %arrayidx = getelementptr inbounds nuw i8, ptr %memory, i64 %addr
  %0 = load i32, ptr %expected, align 4, !tbaa !12
  %conv = trunc i32 %0 to i8
  %conv1 = trunc i32 %desired to i8
  %1 = cmpxchg ptr %arrayidx, i8 %conv, i8 %conv1 seq_cst seq_cst, align 1
  %2 = extractvalue { i8, i1 } %1, 0
  %conv2 = zext i8 %2 to i32
  store i32 %conv2, ptr %expected, align 4, !tbaa !12
  ret ptr %memory
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @__remill_flag_computation_zero(i1 noundef returned zeroext %result, ...) local_unnamed_addr #7 {
entry:
  ret i1 %result
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @__remill_flag_computation_sign(i1 noundef returned zeroext %result, ...) local_unnamed_addr #7 {
entry:
  ret i1 %result
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @__remill_flag_computation_overflow(i1 noundef returned zeroext %result, ...) local_unnamed_addr #7 {
entry:
  ret i1 %result
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @__remill_flag_computation_carry(i1 noundef returned zeroext %result, ...) local_unnamed_addr #7 {
entry:
  ret i1 %result
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @__remill_compare_sle(i1 noundef returned zeroext %result) local_unnamed_addr #7 {
entry:
  ret i1 %result
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @__remill_compare_slt(i1 noundef returned zeroext %result) local_unnamed_addr #7 {
entry:
  ret i1 %result
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @__remill_compare_sge(i1 noundef returned zeroext %result) local_unnamed_addr #7 {
entry:
  ret i1 %result
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @__remill_compare_sgt(i1 noundef returned zeroext %result) local_unnamed_addr #7 {
entry:
  ret i1 %result
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @__remill_compare_ule(i1 noundef returned zeroext %result) local_unnamed_addr #7 {
entry:
  ret i1 %result
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @__remill_compare_ult(i1 noundef returned zeroext %result) local_unnamed_addr #7 {
entry:
  ret i1 %result
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @__remill_compare_ugt(i1 noundef returned zeroext %result) local_unnamed_addr #7 {
entry:
  ret i1 %result
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @__remill_compare_uge(i1 noundef returned zeroext %result) local_unnamed_addr #7 {
entry:
  ret i1 %result
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @__remill_compare_eq(i1 noundef returned zeroext %result) local_unnamed_addr #7 {
entry:
  ret i1 %result
}

; Function Attrs: alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @__remill_compare_neq(i1 noundef returned zeroext %result) local_unnamed_addr #7 {
entry:
  ret i1 %result
}

attributes #0 = { mustprogress uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { alwaysinline mustprogress uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #4 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #5 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #7 = { alwaysinline mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #8 = { alwaysinline mustprogress nofree norecurse nounwind willreturn memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #9 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"Ubuntu clang version 20.1.8 (++20250708082409+6fb913d3e2ec-1~exp1~20250708202428.132)"}
!5 = !{!6, !6, i64 0}
!6 = !{!"long", !7, i64 0}
!7 = !{!"omnipotent char", !8, i64 0}
!8 = !{!"Simple C++ TBAA"}
!9 = !{!10, !10, i64 0}
!10 = !{!"p1 omnipotent char", !11, i64 0}
!11 = !{!"any pointer", !7, i64 0}
!12 = !{!13, !13, i64 0}
!13 = !{!"int", !7, i64 0}
