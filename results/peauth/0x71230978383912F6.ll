; ModuleID = 'OutputModule'
source_filename = "OutputModule"

; Function Attrs: alwaysinline mustprogress uwtable
define dso_local i64 @__warbird_vm.10(ptr noalias noundef %memory, ptr noalias noundef %vsp, i64 noundef %arg0, i64 noundef %arg1, i64 noundef %arg2, i64 noundef %arg3) local_unnamed_addr #0 {
entry:
  %0 = alloca ptr, align 8
  store volatile ptr %vsp, ptr %0, align 8
  %.0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0. = load volatile ptr, ptr %0, align 8
  %.0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0.320 = load volatile ptr, ptr %0, align 8
  %1 = getelementptr i8, ptr %vsp, i64 8
  %2 = getelementptr i8, ptr %vsp, i64 -8
  store i64 0, ptr %2, align 1
  tail call void @llvm.memset.p0.i64(ptr noundef nonnull align 1 dereferenceable(16) %1, i8 0, i64 16, i1 false)
  %3 = getelementptr i8, ptr %vsp, i64 -64
  store i64 -102195479628765740, ptr %3, align 1
  %4 = tail call i64 @ext_0x1c0007314(i64 384) #4
  %5 = icmp eq i64 %4, 0
  br i1 %5, label %__warbird_vm.9.exit, label %handler_0x2bd0288f1ef13943.i

handler_0x8f40999f97853d47.i:                     ; preds = %handler_0x2bd0288f1ef13943.i, %handler_0x8f40999f97853d47.i
  %6 = phi i64 [ %751, %handler_0x2bd0288f1ef13943.i ], [ %403, %handler_0x8f40999f97853d47.i ]
  %7 = phi i64 [ %746, %handler_0x2bd0288f1ef13943.i ], [ %398, %handler_0x8f40999f97853d47.i ]
  %8 = phi i64 [ %739, %handler_0x2bd0288f1ef13943.i ], [ %391, %handler_0x8f40999f97853d47.i ]
  %9 = phi i64 [ %733, %handler_0x2bd0288f1ef13943.i ], [ %385, %handler_0x8f40999f97853d47.i ]
  %10 = phi i64 [ %728, %handler_0x2bd0288f1ef13943.i ], [ %380, %handler_0x8f40999f97853d47.i ]
  %11 = phi i64 [ %721, %handler_0x2bd0288f1ef13943.i ], [ %373, %handler_0x8f40999f97853d47.i ]
  %12 = phi i64 [ %715, %handler_0x2bd0288f1ef13943.i ], [ %367, %handler_0x8f40999f97853d47.i ]
  %13 = phi i64 [ %709, %handler_0x2bd0288f1ef13943.i ], [ %361, %handler_0x8f40999f97853d47.i ]
  %14 = phi i64 [ %703, %handler_0x2bd0288f1ef13943.i ], [ %355, %handler_0x8f40999f97853d47.i ]
  %15 = phi i64 [ %697, %handler_0x2bd0288f1ef13943.i ], [ %349, %handler_0x8f40999f97853d47.i ]
  %16 = phi i64 [ %691, %handler_0x2bd0288f1ef13943.i ], [ %343, %handler_0x8f40999f97853d47.i ]
  %17 = phi i64 [ %685, %handler_0x2bd0288f1ef13943.i ], [ %337, %handler_0x8f40999f97853d47.i ]
  %18 = phi i64 [ %679, %handler_0x2bd0288f1ef13943.i ], [ %331, %handler_0x8f40999f97853d47.i ]
  %19 = phi i64 [ %674, %handler_0x2bd0288f1ef13943.i ], [ %326, %handler_0x8f40999f97853d47.i ]
  %20 = phi i64 [ %667, %handler_0x2bd0288f1ef13943.i ], [ %319, %handler_0x8f40999f97853d47.i ]
  %21 = phi i64 [ %661, %handler_0x2bd0288f1ef13943.i ], [ %313, %handler_0x8f40999f97853d47.i ]
  %22 = phi i64 [ %650, %handler_0x2bd0288f1ef13943.i ], [ %301, %handler_0x8f40999f97853d47.i ]
  %23 = phi i64 [ %645, %handler_0x2bd0288f1ef13943.i ], [ %295, %handler_0x8f40999f97853d47.i ]
  %24 = phi i64 [ %638, %handler_0x2bd0288f1ef13943.i ], [ %289, %handler_0x8f40999f97853d47.i ]
  %25 = phi i64 [ %628, %handler_0x2bd0288f1ef13943.i ], [ %282, %handler_0x8f40999f97853d47.i ]
  %26 = phi i64 [ %624, %handler_0x2bd0288f1ef13943.i ], [ %277, %handler_0x8f40999f97853d47.i ]
  %27 = phi i64 [ %614, %handler_0x2bd0288f1ef13943.i ], [ %270, %handler_0x8f40999f97853d47.i ]
  %28 = phi i64 [ %607, %handler_0x2bd0288f1ef13943.i ], [ %264, %handler_0x8f40999f97853d47.i ]
  %29 = phi i64 [ %600, %handler_0x2bd0288f1ef13943.i ], [ %258, %handler_0x8f40999f97853d47.i ]
  %30 = phi i64 [ %593, %handler_0x2bd0288f1ef13943.i ], [ %252, %handler_0x8f40999f97853d47.i ]
  %31 = phi i64 [ %586, %handler_0x2bd0288f1ef13943.i ], [ %246, %handler_0x8f40999f97853d47.i ]
  %32 = phi i64 [ %579, %handler_0x2bd0288f1ef13943.i ], [ %240, %handler_0x8f40999f97853d47.i ]
  %33 = phi i64 [ %572, %handler_0x2bd0288f1ef13943.i ], [ %234, %handler_0x8f40999f97853d47.i ]
  %34 = phi i64 [ %568, %handler_0x2bd0288f1ef13943.i ], [ %229, %handler_0x8f40999f97853d47.i ]
  %.sink341 = phi i64 [ %757, %handler_0x2bd0288f1ef13943.i ], [ %409, %handler_0x8f40999f97853d47.i ]
  %.sink338 = phi i64 [ %558, %handler_0x2bd0288f1ef13943.i ], [ %222, %handler_0x8f40999f97853d47.i ]
  %.sink = phi i64 [ %654, %handler_0x2bd0288f1ef13943.i ], [ %306, %handler_0x8f40999f97853d47.i ]
  %35 = phi i64 [ %651, %handler_0x2bd0288f1ef13943.i ], [ %304, %handler_0x8f40999f97853d47.i ]
  %36 = trunc i64 %.sink341 to i32
  store i32 %36, ptr %534, align 1
  %37 = lshr i64 %.sink341, 32
  %38 = and i64 %.sink338, 4294967295
  %39 = mul nuw i64 %.sink, 3485148546
  %40 = add nuw nsw i64 %38, %37
  %41 = add nuw i64 %40, %39
  %42 = and i64 %34, 4294967295
  %43 = mul nuw nsw i64 %.sink, 1556704042
  %44 = trunc i64 %41 to i32
  store i32 %44, ptr %545, align 1
  %45 = lshr i64 %41, 32
  %46 = add nuw nsw i64 %43, %42
  %47 = add nuw nsw i64 %46, %45
  %48 = and i64 %33, 4294967295
  %49 = mul nuw nsw i64 %.sink, 1963452294
  %50 = trunc i64 %47 to i32
  store i32 %50, ptr %552, align 1
  %51 = lshr i64 %47, 32
  %52 = add nuw nsw i64 %49, %48
  %53 = add nuw nsw i64 %52, %51
  %54 = mul nuw nsw i64 %.sink, 1664356395
  %55 = and i64 %32, 4294967295
  %56 = trunc i64 %53 to i32
  store i32 %56, ptr %559, align 1
  %57 = lshr i64 %53, 32
  %58 = add nuw nsw i64 %54, %55
  %59 = add nuw nsw i64 %58, %57
  %60 = trunc i64 %59 to i32
  store i32 %60, ptr %564, align 1
  %61 = lshr i64 %59, 32
  %62 = and i64 %31, 4294967295
  %63 = mul nuw i64 %.sink, 2577298597
  %64 = add nuw i64 %63, %62
  %65 = add nuw i64 %64, %61
  %66 = trunc i64 %65 to i32
  store i32 %66, ptr %573, align 1
  %67 = lshr i64 %65, 32
  %68 = and i64 %30, 4294967295
  %69 = mul nuw i64 %.sink, 2493713827
  %70 = add nuw i64 %69, %68
  %71 = add nuw i64 %70, %67
  %72 = mul nuw nsw i64 %.sink, 1525049620
  %73 = and i64 %29, 4294967295
  %74 = trunc i64 %71 to i32
  store i32 %74, ptr %580, align 1
  %75 = lshr i64 %71, 32
  %76 = add nuw nsw i64 %72, %73
  %77 = add nuw nsw i64 %76, %75
  %78 = trunc i64 %77 to i32
  %79 = and i64 %28, 4294967295
  store i32 %78, ptr %587, align 1
  %80 = lshr i64 %77, 32
  %81 = mul nuw nsw i64 %.sink, 1018546740
  %82 = add nuw nsw i64 %81, %79
  %83 = add nuw nsw i64 %82, %80
  %84 = trunc i64 %83 to i32
  store i32 %84, ptr %594, align 1
  %85 = and i64 %27, 4294967295
  %86 = mul nuw i64 %.sink, 2244399836
  %87 = lshr i64 %83, 32
  %88 = add nuw i64 %86, %85
  %89 = add nuw i64 %88, %87
  %90 = mul nuw i64 %.sink, 3630195635
  %91 = trunc i64 %89 to i32
  store i32 %91, ptr %601, align 1
  %92 = and i64 %26, 4294967295
  %93 = lshr i64 %89, 32
  %94 = add nuw i64 %90, %92
  %95 = add nuw i64 %94, %93
  %96 = trunc i64 %95 to i32
  store i32 %96, ptr %608, align 1
  %97 = lshr i64 %95, 32
  %98 = and i64 %25, 4294967295
  %99 = mul nuw i64 %.sink, 2314503259
  %100 = mul nuw i64 %.sink, 2883684570
  %101 = add nuw i64 %99, %98
  %102 = add nuw i64 %101, %97
  %103 = trunc i64 %102 to i32
  store i32 %103, ptr %615, align 1
  %104 = and i64 %24, 4294967295
  %105 = lshr i64 %102, 32
  %106 = add nuw i64 %100, %104
  %107 = add nuw i64 %106, %105
  %108 = trunc i64 %107 to i32
  store i32 %108, ptr %619, align 1
  %109 = lshr i64 %107, 32
  %110 = and i64 %23, 4294967295
  %111 = mul nuw i64 %.sink, 3519938031
  %112 = add nuw i64 %111, %110
  %113 = add nuw i64 %112, %109
  %114 = mul nuw i64 %.sink, 3514121767
  %115 = trunc i64 %113 to i32
  store i32 %115, ptr %629, align 1
  %116 = lshr i64 %113, 32
  %117 = and i64 %22, 4294967295
  %118 = add nuw i64 %114, %117
  %119 = add nuw i64 %118, %116
  %120 = trunc i64 %119 to i32
  store i32 %120, ptr %632, align 1
  %121 = lshr i64 %119, 32
  %122 = add nuw nsw i64 %121, %35
  %123 = trunc i64 %122 to i32
  store i32 %123, ptr %640, align 1
  %124 = lshr i64 %122, 32
  %125 = load i32, ptr %758, align 1
  %126 = tail call i32 @llvm.bswap.i32(i32 %125)
  %127 = zext i32 %126 to i64
  %128 = and i64 %21, 4294967295
  %129 = mul nuw i64 %127, 2779687654
  %130 = add nuw i64 %129, %128
  %131 = and i64 %20, 4294967295
  %132 = lshr i64 %130, 32
  %133 = mul nuw nsw i64 %127, 320181288
  %134 = add nuw nsw i64 %133, %131
  %135 = add nuw nsw i64 %134, %132
  %136 = and i64 %19, 4294967295
  %137 = mul nuw nsw i64 %127, 2085748800
  %138 = lshr i64 %135, 32
  %139 = add nuw nsw i64 %137, %136
  %140 = add nuw nsw i64 %139, %138
  %141 = and i64 %18, 4294967295
  %142 = lshr i64 %140, 32
  %143 = and i64 %17, 4294967295
  %144 = mul nuw nsw i64 %127, 1035437195
  %145 = add nuw nsw i64 %144, %141
  %146 = add nuw nsw i64 %145, %142
  %147 = lshr i64 %146, 32
  %148 = mul nuw nsw i64 %127, 1539831101
  %149 = add nuw nsw i64 %148, %143
  %150 = add nuw nsw i64 %149, %147
  %151 = and i64 %16, 4294967295
  %152 = mul nuw nsw i64 %127, 1342089518
  %153 = and i64 %15, 4294967295
  %154 = lshr i64 %150, 32
  %155 = add nuw nsw i64 %152, %151
  %156 = add nuw nsw i64 %155, %154
  %157 = mul nuw i64 %127, 3081357628
  %158 = lshr i64 %156, 32
  %159 = add nuw i64 %157, %153
  %160 = add nuw i64 %159, %158
  %161 = and i64 %14, 4294967295
  %162 = and i64 %13, 4294967295
  %163 = mul nuw i64 %127, 3911084142
  %164 = lshr i64 %160, 32
  %165 = add nuw i64 %163, %161
  %166 = add nuw i64 %165, %164
  %167 = lshr i64 %166, 32
  %168 = mul nuw i64 %127, 2261792098
  %169 = add nuw i64 %168, %162
  %170 = add nuw i64 %169, %167
  %171 = and i64 %12, 4294967295
  %172 = mul nuw i64 %127, 2327232070
  %173 = lshr i64 %170, 32
  %174 = add nuw i64 %172, %171
  %175 = add nuw i64 %174, %173
  %176 = and i64 %11, 4294967295
  %177 = lshr i64 %175, 32
  %178 = mul nuw nsw i64 %127, 1581598214
  %179 = add nuw nsw i64 %178, %176
  %180 = add nuw nsw i64 %179, %177
  %181 = lshr i64 %180, 32
  %182 = mul nuw nsw i64 %127, 262405431
  %183 = and i64 %10, 4294967295
  %184 = add nuw nsw i64 %182, %183
  %185 = add nuw nsw i64 %184, %181
  %186 = and i64 %9, 4294967295
  %187 = mul nuw i64 %127, 4268121131
  %188 = lshr i64 %185, 32
  %189 = add nuw i64 %187, %186
  %190 = add nuw i64 %189, %188
  %191 = and i64 %8, 4294967295
  %192 = lshr i64 %190, 32
  %193 = mul nuw nsw i64 %127, 467819362
  %194 = add nuw nsw i64 %193, %191
  %195 = add nuw nsw i64 %194, %192
  %196 = and i64 %7, 4294967295
  %197 = lshr i64 %195, 32
  %198 = mul nuw nsw i64 %127, 1069005387
  %199 = add nuw nsw i64 %198, %196
  %200 = add nuw nsw i64 %199, %197
  %201 = and i64 %6, 4294967295
  %202 = and i64 %.sink341, 4294967295
  %203 = lshr i64 %200, 32
  %204 = mul nuw i64 %127, 2807488134
  %205 = add nuw i64 %204, %201
  %206 = add nuw i64 %205, %203
  %207 = mul nuw nsw i64 %127, 1806027563
  %208 = lshr i64 %206, 32
  %209 = add nuw nsw i64 %207, %202
  %210 = add nuw nsw i64 %209, %208
  %211 = and i64 %41, 4294967295
  %212 = trunc i64 %210 to i32
  store i32 %212, ptr %534, align 1
  %213 = lshr i64 %210, 32
  %214 = mul nuw i64 %127, 3864499697
  %215 = add nuw i64 %214, %211
  %216 = add nuw i64 %215, %213
  %217 = and i64 %47, 4294967295
  %218 = trunc i64 %216 to i32
  store i32 %218, ptr %545, align 1
  %219 = lshr i64 %216, 32
  %220 = mul nuw i64 %127, 3664390961
  %221 = add nuw i64 %220, %217
  %222 = add nuw i64 %221, %219
  %223 = and i64 %53, 4294967295
  %224 = trunc i64 %222 to i32
  store i32 %224, ptr %552, align 1
  %225 = lshr i64 %222, 32
  %226 = mul nuw nsw i64 %127, 1365959936
  %227 = and i64 %59, 4294967295
  %228 = add nuw nsw i64 %226, %223
  %229 = add nuw nsw i64 %228, %225
  %230 = trunc i64 %229 to i32
  store i32 %230, ptr %559, align 1
  %231 = lshr i64 %229, 32
  %232 = mul nuw nsw i64 %127, 1334822367
  %233 = add nuw nsw i64 %232, %227
  %234 = add nuw nsw i64 %233, %231
  %235 = and i64 %65, 4294967295
  %236 = trunc i64 %234 to i32
  store i32 %236, ptr %564, align 1
  %237 = lshr i64 %234, 32
  %238 = mul nuw i64 %127, 3292237580
  %239 = add nuw i64 %238, %235
  %240 = add nuw i64 %239, %237
  %241 = and i64 %71, 4294967295
  %242 = trunc i64 %240 to i32
  store i32 %242, ptr %573, align 1
  %243 = lshr i64 %240, 32
  %244 = mul nuw i64 %127, 3236423124
  %245 = add nuw i64 %244, %241
  %246 = add nuw i64 %245, %243
  %247 = trunc i64 %246 to i32
  store i32 %247, ptr %580, align 1
  %248 = and i64 %77, 4294967295
  %249 = mul nuw i64 %127, 2455260496
  %250 = lshr i64 %246, 32
  %251 = add nuw i64 %249, %248
  %252 = add nuw i64 %251, %250
  %253 = and i64 %83, 4294967295
  %254 = trunc i64 %252 to i32
  store i32 %254, ptr %587, align 1
  %255 = mul nuw nsw i64 %127, 885352260
  %256 = lshr i64 %252, 32
  %257 = add nuw nsw i64 %255, %253
  %258 = add nuw nsw i64 %257, %256
  %259 = and i64 %89, 4294967295
  %260 = trunc i64 %258 to i32
  store i32 %260, ptr %594, align 1
  %261 = lshr i64 %258, 32
  %262 = mul nuw i64 %127, 4162433239
  %263 = add nuw i64 %262, %259
  %264 = add nuw i64 %263, %261
  %265 = and i64 %95, 4294967295
  %266 = trunc i64 %264 to i32
  store i32 %266, ptr %601, align 1
  %267 = mul nuw i64 %127, 4190231582
  %268 = lshr i64 %264, 32
  %269 = add nuw i64 %265, %267
  %270 = add nuw i64 %269, %268
  %271 = and i64 %102, 4294967295
  %272 = trunc i64 %270 to i32
  store i32 %272, ptr %608, align 1
  %273 = lshr i64 %270, 32
  %274 = and i64 %107, 4294967295
  %275 = mul nuw i64 %127, 2678497547
  %276 = add nuw i64 %271, %275
  %277 = add nuw i64 %276, %273
  %278 = trunc i64 %277 to i32
  store i32 %278, ptr %615, align 1
  %279 = lshr i64 %277, 32
  %280 = mul nuw nsw i64 %127, 2079329235
  %281 = add nuw nsw i64 %274, %280
  %282 = add nuw nsw i64 %281, %279
  %283 = and i64 %113, 4294967295
  %284 = trunc i64 %282 to i32
  store i32 %284, ptr %619, align 1
  %285 = and i64 %119, 4294967295
  %286 = lshr i64 %282, 32
  %287 = mul nuw i64 %127, 3306885437
  %288 = add nuw i64 %283, %287
  %289 = add nuw i64 %288, %286
  %290 = trunc i64 %289 to i32
  store i32 %290, ptr %629, align 1
  %291 = mul nuw i64 %127, 3085585469
  %292 = and i64 %122, 4294967295
  %293 = lshr i64 %289, 32
  %294 = add nuw i64 %285, %291
  %295 = add nuw i64 %294, %293
  %296 = trunc i64 %295 to i32
  store i32 %296, ptr %632, align 1
  %297 = and i64 %130, 4294967295
  %298 = mul nuw nsw i64 %127, 1093371459
  %299 = lshr i64 %295, 32
  %300 = add nuw nsw i64 %292, %298
  %301 = add nuw nsw i64 %300, %299
  %302 = trunc i64 %301 to i32
  store i32 %302, ptr %640, align 1
  %303 = lshr i64 %301, 32
  %304 = add nuw nsw i64 %303, %124
  %305 = mul i64 %130, 4166321959
  %306 = and i64 %305, 4294967295
  %307 = mul nuw nsw i64 %306, 1667368809
  %308 = add nuw nsw i64 %307, %297
  %309 = lshr i64 %308, 32
  %310 = and i64 %135, 4294967295
  %311 = mul nuw nsw i64 %306, 148686674
  %312 = add nuw nsw i64 %310, %311
  %313 = add nuw nsw i64 %312, %309
  %314 = mul nuw i64 %306, 3768258774
  %315 = trunc i64 %313 to i32
  store i32 %315, ptr %429, align 1
  %316 = and i64 %140, 4294967295
  %317 = lshr i64 %313, 32
  %318 = add nuw i64 %316, %314
  %319 = add nuw i64 %318, %317
  %320 = trunc i64 %319 to i32
  store i32 %320, ptr %434, align 1
  %321 = and i64 %146, 4294967295
  %322 = lshr i64 %319, 32
  %323 = and i64 %150, 4294967295
  %324 = mul nuw i64 %306, 2198378334
  %325 = add nuw i64 %321, %324
  %326 = add nuw i64 %325, %322
  %327 = trunc i64 %326 to i32
  store i32 %327, ptr %428, align 1
  %328 = lshr i64 %326, 32
  %329 = mul nuw nsw i64 %306, 2030586897
  %330 = add nuw nsw i64 %323, %329
  %331 = add nuw nsw i64 %330, %328
  %332 = mul nuw i64 %306, 2950810761
  %333 = trunc i64 %331 to i32
  store i32 %333, ptr %447, align 1
  %334 = lshr i64 %331, 32
  %335 = and i64 %156, 4294967295
  %336 = add nuw i64 %335, %332
  %337 = add nuw i64 %336, %334
  %338 = and i64 %160, 4294967295
  %339 = trunc i64 %337 to i32
  store i32 %339, ptr %451, align 1
  %340 = lshr i64 %337, 32
  %341 = mul nuw nsw i64 %306, 1463192792
  %342 = add nuw nsw i64 %338, %341
  %343 = add nuw nsw i64 %342, %340
  %344 = mul nuw nsw i64 %306, 1266992699
  %345 = and i64 %166, 4294967295
  %346 = trunc i64 %343 to i32
  store i32 %346, ptr %461, align 1
  %347 = lshr i64 %343, 32
  %348 = add nuw nsw i64 %345, %344
  %349 = add nuw nsw i64 %348, %347
  %350 = trunc i64 %349 to i32
  store i32 %350, ptr %465, align 1
  %351 = lshr i64 %349, 32
  %352 = and i64 %170, 4294967295
  %353 = mul nuw i64 %306, 2150553014
  %354 = add nuw i64 %352, %353
  %355 = add nuw i64 %354, %351
  %356 = trunc i64 %355 to i32
  store i32 %356, ptr %475, align 1
  %357 = lshr i64 %355, 32
  %358 = and i64 %175, 4294967295
  %359 = mul nuw i64 %306, 2965162018
  %360 = add nuw i64 %358, %359
  %361 = add nuw i64 %360, %357
  %362 = trunc i64 %361 to i32
  store i32 %362, ptr %478, align 1
  %363 = lshr i64 %361, 32
  %364 = and i64 %180, 4294967295
  %365 = mul nuw i64 %306, 2548134123
  %366 = add nuw i64 %364, %365
  %367 = add nuw i64 %366, %363
  %368 = trunc i64 %367 to i32
  store i32 %368, ptr %489, align 1
  %369 = and i64 %185, 4294967295
  %370 = lshr i64 %367, 32
  %371 = mul nuw i64 %306, 3849542690
  %372 = add nuw i64 %369, %371
  %373 = add nuw i64 %372, %370
  %374 = trunc i64 %373 to i32
  store i32 %374, ptr %496, align 1
  %375 = mul nuw i64 %306, 2562744691
  %376 = and i64 %190, 4294967295
  %377 = lshr i64 %373, 32
  %378 = mul nuw nsw i64 %306, 524751465
  %379 = add nuw nsw i64 %376, %378
  %380 = add nuw nsw i64 %379, %377
  %381 = trunc i64 %380 to i32
  store i32 %381, ptr %505, align 1
  %382 = lshr i64 %380, 32
  %383 = and i64 %195, 4294967295
  %384 = add nuw i64 %383, %375
  %385 = add nuw i64 %384, %382
  %386 = trunc i64 %385 to i32
  store i32 %386, ptr %510, align 1
  %387 = lshr i64 %385, 32
  %388 = and i64 %200, 4294967295
  %389 = mul nuw i64 %306, 4111372729
  %390 = add nuw i64 %388, %389
  %391 = add nuw i64 %390, %387
  %392 = mul nuw i64 %306, 2771319969
  %393 = trunc i64 %391 to i32
  store i32 %393, ptr %517, align 1
  %394 = and i64 %206, 4294967295
  %395 = and i64 %210, 4294967295
  %396 = lshr i64 %391, 32
  %397 = add nuw i64 %394, %392
  %398 = add nuw i64 %397, %396
  %399 = trunc i64 %398 to i32
  store i32 %399, ptr %524, align 1
  %400 = lshr i64 %398, 32
  %401 = mul nuw nsw i64 %306, 711425752
  %402 = add nuw nsw i64 %395, %401
  %403 = add nuw nsw i64 %402, %400
  %404 = trunc i64 %403 to i32
  store i32 %404, ptr %531, align 1
  %405 = mul nuw i64 %306, 2289695153
  %406 = lshr i64 %403, 32
  %407 = and i64 %216, 4294967295
  %408 = add nuw i64 %407, %405
  %409 = add nuw i64 %408, %406
  br label %handler_0x8f40999f97853d47.i

handler_0x2bd0288f1ef13943.i:                     ; preds = %entry
  %410 = getelementptr i8, ptr %vsp, i64 -56
  %411 = getelementptr i8, ptr %vsp, i64 -24
  store i64 %4, ptr %411, align 1
  store i64 -1202353327352992111, ptr %3, align 1
  store i64 %4, ptr %410, align 1
  %412 = getelementptr i8, ptr %vsp, i64 -48
  store i64 0, ptr %412, align 1
  %413 = getelementptr i8, ptr %vsp, i64 -32
  %414 = getelementptr i8, ptr %vsp, i64 -72
  store i64 %arg0, ptr %414, align 1
  %415 = getelementptr i8, ptr %vsp, i64 -80
  store i64 %arg1, ptr %415, align 1
  %416 = getelementptr i8, ptr %vsp, i64 -104
  tail call void @llvm.memset.p0.i64(ptr noundef nonnull align 1 dereferenceable(24) %416, i8 0, i64 24, i1 false)
  %417 = getelementptr i8, ptr %vsp, i64 -120
  store i64 7517012032, ptr %417, align 1
  %418 = getelementptr i8, ptr %vsp, i64 -112
  store i32 0, ptr %418, align 1
  %419 = getelementptr i8, ptr %vsp, i64 -160
  %420 = inttoptr i64 %4 to ptr
  tail call void @llvm.memset.inline.p0.i64(ptr nonnull align 8 %420, i8 0, i64 128, i1 false)
  %421 = inttoptr i64 %arg1 to ptr
  %422 = getelementptr i8, ptr %421, i64 124
  %423 = load i32, ptr %422, align 1
  store i64 3665707951660368763, ptr %419, align 1
  %424 = tail call i32 @llvm.bswap.i32(i32 %423)
  %425 = zext i32 %424 to i64
  %426 = getelementptr i8, ptr %vsp, i64 -152
  %427 = getelementptr i8, ptr %vsp, i64 -144
  store i64 %arg1, ptr %426, align 1
  store i64 7516962208, ptr %427, align 1
  %428 = inttoptr i64 %4 to ptr
  %429 = getelementptr i8, ptr %428, i64 72
  %430 = load i32, ptr %429, align 1
  %431 = zext i32 %430 to i64
  %432 = mul nuw i64 %425, 2779687654
  %433 = add nuw i64 %432, %431
  %434 = getelementptr i8, ptr %428, i64 56
  %435 = load i32, ptr %434, align 1
  %436 = zext i32 %435 to i64
  %437 = lshr i64 %433, 32
  %438 = mul nuw nsw i64 %425, 320181288
  %439 = add nuw nsw i64 %438, %436
  %440 = add nuw nsw i64 %439, %437
  %441 = load i32, ptr %428, align 1
  %442 = zext i32 %441 to i64
  %443 = mul nuw nsw i64 %425, 2085748800
  %444 = lshr i64 %440, 32
  %445 = add nuw nsw i64 %443, %442
  %446 = add nuw nsw i64 %445, %444
  %447 = getelementptr i8, ptr %428, i64 92
  %448 = load i32, ptr %447, align 1
  %449 = zext i32 %448 to i64
  %450 = lshr i64 %446, 32
  %451 = getelementptr i8, ptr %428, i64 88
  %452 = load i32, ptr %451, align 1
  %453 = zext i32 %452 to i64
  %454 = mul nuw nsw i64 %425, 1035437195
  %455 = add nuw nsw i64 %454, %449
  %456 = add nuw nsw i64 %455, %450
  %457 = lshr i64 %456, 32
  %458 = mul nuw nsw i64 %425, 1539831101
  %459 = add nuw nsw i64 %458, %453
  %460 = add nuw nsw i64 %459, %457
  %461 = getelementptr i8, ptr %428, i64 28
  %462 = load i32, ptr %461, align 1
  %463 = zext i32 %462 to i64
  %464 = mul nuw nsw i64 %425, 1342089518
  %465 = getelementptr i8, ptr %428, i64 4
  %466 = load i32, ptr %465, align 1
  %467 = zext i32 %466 to i64
  %468 = lshr i64 %460, 32
  %469 = add nuw nsw i64 %464, %463
  %470 = add nuw nsw i64 %469, %468
  %471 = mul nuw i64 %425, 3081357628
  %472 = lshr i64 %470, 32
  %473 = add nuw i64 %471, %467
  %474 = add nuw i64 %473, %472
  %475 = getelementptr i8, ptr %428, i64 112
  %476 = load i32, ptr %475, align 1
  %477 = zext i32 %476 to i64
  %478 = getelementptr i8, ptr %428, i64 80
  %479 = load i32, ptr %478, align 1
  %480 = zext i32 %479 to i64
  %481 = mul nuw i64 %425, 3911084142
  %482 = lshr i64 %474, 32
  %483 = add nuw i64 %481, %477
  %484 = add nuw i64 %483, %482
  %485 = lshr i64 %484, 32
  %486 = mul nuw i64 %425, 2261792098
  %487 = add nuw i64 %486, %480
  %488 = add nuw i64 %487, %485
  %489 = getelementptr i8, ptr %428, i64 12
  %490 = load i32, ptr %489, align 1
  %491 = zext i32 %490 to i64
  %492 = mul nuw i64 %425, 2327232070
  %493 = lshr i64 %488, 32
  %494 = add nuw i64 %492, %491
  %495 = add nuw i64 %494, %493
  %496 = getelementptr i8, ptr %428, i64 68
  %497 = load i32, ptr %496, align 1
  %498 = zext i32 %497 to i64
  %499 = lshr i64 %495, 32
  %500 = mul nuw nsw i64 %425, 1581598214
  %501 = add nuw nsw i64 %500, %498
  %502 = add nuw nsw i64 %501, %499
  %503 = lshr i64 %502, 32
  %504 = mul nuw nsw i64 %425, 262405431
  %505 = getelementptr i8, ptr %428, i64 104
  %506 = load i32, ptr %505, align 1
  %507 = zext i32 %506 to i64
  %508 = add nuw nsw i64 %504, %507
  %509 = add nuw nsw i64 %508, %503
  %510 = getelementptr i8, ptr %428, i64 20
  %511 = load i32, ptr %510, align 1
  %512 = zext i32 %511 to i64
  %513 = mul nuw i64 %425, 4268121131
  %514 = lshr i64 %509, 32
  %515 = add nuw i64 %513, %512
  %516 = add nuw i64 %515, %514
  %517 = getelementptr i8, ptr %428, i64 100
  %518 = load i32, ptr %517, align 1
  %519 = zext i32 %518 to i64
  %520 = lshr i64 %516, 32
  %521 = mul nuw nsw i64 %425, 467819362
  %522 = add nuw nsw i64 %521, %519
  %523 = add nuw nsw i64 %522, %520
  %524 = getelementptr i8, ptr %428, i64 108
  %525 = load i32, ptr %524, align 1
  %526 = zext i32 %525 to i64
  %527 = lshr i64 %523, 32
  %528 = mul nuw nsw i64 %425, 1069005387
  %529 = add nuw nsw i64 %528, %526
  %530 = add nuw nsw i64 %529, %527
  %531 = getelementptr i8, ptr %428, i64 60
  %532 = load i32, ptr %531, align 1
  %533 = zext i32 %532 to i64
  %534 = getelementptr i8, ptr %428, i64 120
  %535 = load i32, ptr %534, align 1
  %536 = zext i32 %535 to i64
  %537 = lshr i64 %530, 32
  %538 = mul nuw i64 %425, 2807488134
  %539 = add nuw i64 %538, %533
  %540 = add nuw i64 %539, %537
  %541 = mul nuw nsw i64 %425, 1806027563
  %542 = lshr i64 %540, 32
  %543 = add nuw nsw i64 %541, %536
  %544 = add nuw nsw i64 %543, %542
  %545 = getelementptr i8, ptr %428, i64 116
  %546 = load i32, ptr %545, align 1
  %547 = zext i32 %546 to i64
  %548 = lshr i64 %544, 32
  %549 = mul nuw i64 %425, 3864499697
  %550 = add nuw i64 %549, %547
  %551 = add nuw i64 %550, %548
  %552 = getelementptr i8, ptr %428, i64 24
  %553 = load i32, ptr %552, align 1
  %554 = zext i32 %553 to i64
  %555 = lshr i64 %551, 32
  %556 = mul nuw i64 %425, 3664390961
  %557 = add nuw i64 %556, %554
  %558 = add nuw i64 %557, %555
  %559 = getelementptr i8, ptr %428, i64 40
  %560 = load i32, ptr %559, align 1
  %561 = zext i32 %560 to i64
  %562 = lshr i64 %558, 32
  %563 = mul nuw nsw i64 %425, 1365959936
  %564 = getelementptr i8, ptr %428, i64 96
  %565 = load i32, ptr %564, align 1
  %566 = zext i32 %565 to i64
  %567 = add nuw nsw i64 %563, %561
  %568 = add nuw nsw i64 %567, %562
  %569 = lshr i64 %568, 32
  %570 = mul nuw nsw i64 %425, 1334822367
  %571 = add nuw nsw i64 %570, %566
  %572 = add nuw nsw i64 %571, %569
  %573 = getelementptr i8, ptr %428, i64 36
  %574 = load i32, ptr %573, align 1
  %575 = zext i32 %574 to i64
  %576 = lshr i64 %572, 32
  %577 = mul nuw i64 %425, 3292237580
  %578 = add nuw i64 %577, %575
  %579 = add nuw i64 %578, %576
  %580 = getelementptr i8, ptr %428, i64 76
  %581 = load i32, ptr %580, align 1
  %582 = zext i32 %581 to i64
  %583 = lshr i64 %579, 32
  %584 = mul nuw i64 %425, 3236423124
  %585 = add nuw i64 %584, %582
  %586 = add nuw i64 %585, %583
  %587 = getelementptr i8, ptr %428, i64 48
  %588 = load i32, ptr %587, align 1
  %589 = zext i32 %588 to i64
  %590 = mul nuw i64 %425, 2455260496
  %591 = lshr i64 %586, 32
  %592 = add nuw i64 %590, %589
  %593 = add nuw i64 %592, %591
  %594 = getelementptr i8, ptr %428, i64 84
  %595 = load i32, ptr %594, align 1
  %596 = zext i32 %595 to i64
  %597 = mul nuw nsw i64 %425, 885352260
  %598 = lshr i64 %593, 32
  %599 = add nuw nsw i64 %597, %596
  %600 = add nuw nsw i64 %599, %598
  %601 = getelementptr i8, ptr %428, i64 16
  %602 = load i32, ptr %601, align 1
  %603 = zext i32 %602 to i64
  %604 = lshr i64 %600, 32
  %605 = mul nuw i64 %425, 4162433239
  %606 = add nuw i64 %605, %603
  %607 = add nuw i64 %606, %604
  %608 = getelementptr i8, ptr %428, i64 124
  %609 = load i32, ptr %608, align 1
  %610 = zext i32 %609 to i64
  %611 = mul nuw i64 %425, 4190231582
  %612 = lshr i64 %607, 32
  %613 = add nuw i64 %611, %610
  %614 = add nuw i64 %613, %612
  %615 = getelementptr i8, ptr %428, i64 32
  %616 = load i32, ptr %615, align 1
  %617 = zext i32 %616 to i64
  %618 = lshr i64 %614, 32
  %619 = getelementptr i8, ptr %428, i64 64
  %620 = load i32, ptr %619, align 1
  %621 = zext i32 %620 to i64
  %622 = mul nuw i64 %425, 2678497547
  %623 = add nuw i64 %622, %617
  %624 = add nuw i64 %623, %618
  %625 = lshr i64 %624, 32
  %626 = mul nuw nsw i64 %425, 2079329235
  %627 = add nuw nsw i64 %626, %621
  %628 = add nuw nsw i64 %627, %625
  %629 = getelementptr i8, ptr %428, i64 8
  %630 = load i32, ptr %629, align 1
  %631 = zext i32 %630 to i64
  %632 = getelementptr i8, ptr %428, i64 44
  %633 = load i32, ptr %632, align 1
  %634 = zext i32 %633 to i64
  %635 = lshr i64 %628, 32
  %636 = mul nuw i64 %425, 3306885437
  %637 = add nuw i64 %636, %631
  %638 = add nuw i64 %637, %635
  %639 = mul nuw i64 %425, 3085585469
  %640 = getelementptr i8, ptr %428, i64 52
  %641 = load i32, ptr %640, align 1
  %642 = zext i32 %641 to i64
  %643 = lshr i64 %638, 32
  %644 = add nuw i64 %639, %634
  %645 = add nuw i64 %644, %643
  %646 = and i64 %433, 4294967295
  %647 = mul nuw nsw i64 %425, 1093371459
  %648 = lshr i64 %645, 32
  %649 = add nuw nsw i64 %647, %642
  %650 = add nuw nsw i64 %649, %648
  %651 = lshr i64 %650, 32
  %652 = trunc nuw nsw i64 %651 to i32
  store i32 %652, ptr %413, align 1
  %653 = mul i64 %433, 4166321959
  %654 = and i64 %653, 4294967295
  %655 = mul nuw nsw i64 %654, 1667368809
  %656 = add nuw nsw i64 %655, %646
  %657 = lshr i64 %656, 32
  %658 = and i64 %440, 4294967295
  %659 = mul nuw nsw i64 %654, 148686674
  %660 = add nuw nsw i64 %658, %659
  %661 = add nuw nsw i64 %660, %657
  %662 = mul nuw i64 %654, 3768258774
  %663 = trunc i64 %661 to i32
  store i32 %663, ptr %429, align 1
  %664 = and i64 %446, 4294967295
  %665 = lshr i64 %661, 32
  %666 = add nuw i64 %664, %662
  %667 = add nuw i64 %666, %665
  %668 = trunc i64 %667 to i32
  store i32 %668, ptr %434, align 1
  %669 = and i64 %456, 4294967295
  %670 = lshr i64 %667, 32
  %671 = and i64 %460, 4294967295
  %672 = mul nuw i64 %654, 2198378334
  %673 = add nuw i64 %669, %672
  %674 = add nuw i64 %673, %670
  %675 = trunc i64 %674 to i32
  store i32 %675, ptr %428, align 1
  %676 = lshr i64 %674, 32
  %677 = mul nuw nsw i64 %654, 2030586897
  %678 = add nuw nsw i64 %671, %677
  %679 = add nuw nsw i64 %678, %676
  %680 = mul nuw i64 %654, 2950810761
  %681 = trunc i64 %679 to i32
  store i32 %681, ptr %447, align 1
  %682 = lshr i64 %679, 32
  %683 = and i64 %470, 4294967295
  %684 = add nuw i64 %683, %680
  %685 = add nuw i64 %684, %682
  %686 = and i64 %474, 4294967295
  %687 = trunc i64 %685 to i32
  store i32 %687, ptr %451, align 1
  %688 = lshr i64 %685, 32
  %689 = mul nuw nsw i64 %654, 1463192792
  %690 = add nuw nsw i64 %686, %689
  %691 = add nuw nsw i64 %690, %688
  %692 = mul nuw nsw i64 %654, 1266992699
  %693 = and i64 %484, 4294967295
  %694 = trunc i64 %691 to i32
  store i32 %694, ptr %461, align 1
  %695 = lshr i64 %691, 32
  %696 = add nuw nsw i64 %693, %692
  %697 = add nuw nsw i64 %696, %695
  %698 = trunc i64 %697 to i32
  store i32 %698, ptr %465, align 1
  %699 = lshr i64 %697, 32
  %700 = and i64 %488, 4294967295
  %701 = mul nuw i64 %654, 2150553014
  %702 = add nuw i64 %700, %701
  %703 = add nuw i64 %702, %699
  %704 = trunc i64 %703 to i32
  store i32 %704, ptr %475, align 1
  %705 = lshr i64 %703, 32
  %706 = and i64 %495, 4294967295
  %707 = mul nuw i64 %654, 2965162018
  %708 = add nuw i64 %706, %707
  %709 = add nuw i64 %708, %705
  %710 = trunc i64 %709 to i32
  store i32 %710, ptr %478, align 1
  %711 = lshr i64 %709, 32
  %712 = and i64 %502, 4294967295
  %713 = mul nuw i64 %654, 2548134123
  %714 = add nuw i64 %712, %713
  %715 = add nuw i64 %714, %711
  %716 = trunc i64 %715 to i32
  store i32 %716, ptr %489, align 1
  %717 = and i64 %509, 4294967295
  %718 = lshr i64 %715, 32
  %719 = mul nuw i64 %654, 3849542690
  %720 = add nuw i64 %717, %719
  %721 = add nuw i64 %720, %718
  %722 = trunc i64 %721 to i32
  store i32 %722, ptr %496, align 1
  %723 = mul nuw i64 %654, 2562744691
  %724 = and i64 %516, 4294967295
  %725 = lshr i64 %721, 32
  %726 = mul nuw nsw i64 %654, 524751465
  %727 = add nuw nsw i64 %724, %726
  %728 = add nuw nsw i64 %727, %725
  %729 = trunc i64 %728 to i32
  store i32 %729, ptr %505, align 1
  %730 = lshr i64 %728, 32
  %731 = and i64 %523, 4294967295
  %732 = add nuw i64 %731, %723
  %733 = add nuw i64 %732, %730
  %734 = trunc i64 %733 to i32
  store i32 %734, ptr %510, align 1
  %735 = lshr i64 %733, 32
  %736 = and i64 %530, 4294967295
  %737 = mul nuw i64 %654, 4111372729
  %738 = add nuw i64 %736, %737
  %739 = add nuw i64 %738, %735
  %740 = mul nuw i64 %654, 2771319969
  %741 = trunc i64 %739 to i32
  store i32 %741, ptr %517, align 1
  %742 = and i64 %540, 4294967295
  %743 = and i64 %544, 4294967295
  %744 = lshr i64 %739, 32
  %745 = add nuw i64 %742, %740
  %746 = add nuw i64 %745, %744
  %747 = trunc i64 %746 to i32
  store i32 %747, ptr %524, align 1
  %748 = lshr i64 %746, 32
  %749 = mul nuw nsw i64 %654, 711425752
  %750 = add nuw nsw i64 %743, %749
  %751 = add nuw nsw i64 %750, %748
  %752 = trunc i64 %751 to i32
  store i32 %752, ptr %531, align 1
  %753 = mul nuw i64 %654, 2289695153
  %754 = lshr i64 %751, 32
  %755 = and i64 %551, 4294967295
  %756 = add nuw i64 %755, %753
  %757 = add nuw i64 %756, %754
  %758 = getelementptr i8, ptr inttoptr (i64 120 to ptr), i64 %arg1
  br label %handler_0x8f40999f97853d47.i

__warbird_vm.9.exit:                              ; preds = %entry
  ret i64 0
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr writeonly captures(none), i8, i64, i1 immarg) #1

; Function Attrs: memory(none)
declare i64 @ext_0x1c0007314(i64) #2

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.bswap.i32(i32) #3

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.inline.p0.i64(ptr writeonly captures(none), i8, i64, i1 immarg) #1

attributes #0 = { alwaysinline mustprogress uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #2 = { memory(none) }
attributes #3 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #4 = { nounwind }
