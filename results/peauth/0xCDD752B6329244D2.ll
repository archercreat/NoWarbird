; ModuleID = 'OutputModule'
source_filename = "OutputModule"

; Function Attrs: alwaysinline mustprogress uwtable
define dso_local i64 @__warbird_vm.10(ptr noalias noundef %memory, ptr noalias noundef %vsp, i64 noundef %arg0, i64 noundef %arg1, i64 noundef %arg2, i64 noundef %arg3) local_unnamed_addr #0 {
entry:
  %0 = alloca ptr, align 8
  store volatile ptr %vsp, ptr %0, align 8
  %.0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0. = load volatile ptr, ptr %0, align 8
  %.0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0..0.269 = load volatile ptr, ptr %0, align 8
  %1 = getelementptr i8, ptr %vsp, i64 8
  %2 = getelementptr i8, ptr %vsp, i64 -8
  store i64 0, ptr %2, align 1
  tail call void @llvm.memset.p0.i64(ptr noundef nonnull align 1 dereferenceable(16) %1, i8 0, i64 16, i1 false)
  %3 = getelementptr i8, ptr %vsp, i64 -64
  store i64 -8849124087992860222, ptr %3, align 1
  %4 = tail call i64 @ext_0x1c0007314(i64 384) #4
  %5 = icmp eq i64 %4, 0
  br i1 %5, label %__warbird_vm.9.exit, label %handler_0xa1a610b3a4c8df8d.i

handler_0x221109d10e6faffe.i:                     ; preds = %handler_0xa1a610b3a4c8df8d.i, %handler_0x221109d10e6faffe.i
  %6 = phi i32 [ %.pre300, %handler_0xa1a610b3a4c8df8d.i ], [ %392, %handler_0x221109d10e6faffe.i ]
  %7 = phi i32 [ %.pre299, %handler_0xa1a610b3a4c8df8d.i ], [ %389, %handler_0x221109d10e6faffe.i ]
  %8 = phi i32 [ %.pre298, %handler_0xa1a610b3a4c8df8d.i ], [ %383, %handler_0x221109d10e6faffe.i ]
  %9 = phi i32 [ %.pre297, %handler_0xa1a610b3a4c8df8d.i ], [ %378, %handler_0x221109d10e6faffe.i ]
  %10 = phi i32 [ %.pre296, %handler_0xa1a610b3a4c8df8d.i ], [ %372, %handler_0x221109d10e6faffe.i ]
  %11 = phi i32 [ %.pre295, %handler_0xa1a610b3a4c8df8d.i ], [ %365, %handler_0x221109d10e6faffe.i ]
  %12 = phi i32 [ %.pre294, %handler_0xa1a610b3a4c8df8d.i ], [ %360, %handler_0x221109d10e6faffe.i ]
  %13 = phi i32 [ %.pre293, %handler_0xa1a610b3a4c8df8d.i ], [ %348, %handler_0x221109d10e6faffe.i ]
  %14 = phi i32 [ %.pre292, %handler_0xa1a610b3a4c8df8d.i ], [ %353, %handler_0x221109d10e6faffe.i ]
  %15 = phi i32 [ %.pre291, %handler_0xa1a610b3a4c8df8d.i ], [ %342, %handler_0x221109d10e6faffe.i ]
  %16 = phi i32 [ %.pre290, %handler_0xa1a610b3a4c8df8d.i ], [ %336, %handler_0x221109d10e6faffe.i ]
  %17 = phi i32 [ %.pre289, %handler_0xa1a610b3a4c8df8d.i ], [ %329, %handler_0x221109d10e6faffe.i ]
  %18 = phi i32 [ %.pre288, %handler_0xa1a610b3a4c8df8d.i ], [ %324, %handler_0x221109d10e6faffe.i ]
  %19 = phi i32 [ %.pre287, %handler_0xa1a610b3a4c8df8d.i ], [ %317, %handler_0x221109d10e6faffe.i ]
  %20 = phi i32 [ %.pre286, %handler_0xa1a610b3a4c8df8d.i ], [ %313, %handler_0x221109d10e6faffe.i ]
  %21 = phi i32 [ %.pre285, %handler_0xa1a610b3a4c8df8d.i ], [ %305, %handler_0x221109d10e6faffe.i ]
  %22 = phi i32 [ %.pre284, %handler_0xa1a610b3a4c8df8d.i ], [ %300, %handler_0x221109d10e6faffe.i ]
  %23 = phi i32 [ %.pre283, %handler_0xa1a610b3a4c8df8d.i ], [ %293, %handler_0x221109d10e6faffe.i ]
  %24 = phi i32 [ %.pre282, %handler_0xa1a610b3a4c8df8d.i ], [ %289, %handler_0x221109d10e6faffe.i ]
  %25 = phi i32 [ %.pre281, %handler_0xa1a610b3a4c8df8d.i ], [ %281, %handler_0x221109d10e6faffe.i ]
  %26 = phi i32 [ %.pre280, %handler_0xa1a610b3a4c8df8d.i ], [ %276, %handler_0x221109d10e6faffe.i ]
  %27 = phi i32 [ %.pre279, %handler_0xa1a610b3a4c8df8d.i ], [ %271, %handler_0x221109d10e6faffe.i ]
  %28 = phi i32 [ %.pre278, %handler_0xa1a610b3a4c8df8d.i ], [ %264, %handler_0x221109d10e6faffe.i ]
  %29 = phi i32 [ %.pre277, %handler_0xa1a610b3a4c8df8d.i ], [ %257, %handler_0x221109d10e6faffe.i ]
  %30 = phi i32 [ %.pre276, %handler_0xa1a610b3a4c8df8d.i ], [ %252, %handler_0x221109d10e6faffe.i ]
  %31 = phi i32 [ %.pre275, %handler_0xa1a610b3a4c8df8d.i ], [ %245, %handler_0x221109d10e6faffe.i ]
  %32 = phi i32 [ %.pre274, %handler_0xa1a610b3a4c8df8d.i ], [ %239, %handler_0x221109d10e6faffe.i ]
  %33 = phi i32 [ %.pre273, %handler_0xa1a610b3a4c8df8d.i ], [ %234, %handler_0x221109d10e6faffe.i ]
  %34 = phi i32 [ %.pre272, %handler_0xa1a610b3a4c8df8d.i ], [ %228, %handler_0x221109d10e6faffe.i ]
  %35 = phi i32 [ %.pre271, %handler_0xa1a610b3a4c8df8d.i ], [ %221, %handler_0x221109d10e6faffe.i ]
  %36 = phi i32 [ %.pre270, %handler_0xa1a610b3a4c8df8d.i ], [ %210, %handler_0x221109d10e6faffe.i ]
  %37 = phi i32 [ %.pre, %handler_0xa1a610b3a4c8df8d.i ], [ %215, %handler_0x221109d10e6faffe.i ]
  %38 = phi i32 [ %409, %handler_0xa1a610b3a4c8df8d.i ], [ %394, %handler_0x221109d10e6faffe.i ]
  %39 = zext i32 %37 to i64
  %40 = zext i32 %38 to i64
  %41 = zext i32 %36 to i64
  %42 = mul nuw i64 %40, 2328639271
  %43 = add nuw i64 %42, %41
  %44 = lshr i64 %43, 32
  %45 = mul nuw nsw i64 %40, 2060388553
  %46 = zext i32 %35 to i64
  %47 = add nuw nsw i64 %45, %39
  %48 = add nuw nsw i64 %47, %44
  %49 = mul nuw i64 %40, 3348100336
  %50 = lshr i64 %48, 32
  %51 = add nuw i64 %49, %46
  %52 = add nuw i64 %51, %50
  %53 = zext i32 %34 to i64
  %54 = mul nuw i64 %40, 2710119503
  %55 = lshr i64 %52, 32
  %56 = add nuw i64 %54, %53
  %57 = add nuw i64 %56, %55
  %58 = zext i32 %33 to i64
  %59 = lshr i64 %57, 32
  %60 = mul nuw nsw i64 %40, 666745792
  %61 = add nuw nsw i64 %60, %58
  %62 = add nuw nsw i64 %61, %59
  %63 = zext i32 %32 to i64
  %64 = lshr i64 %62, 32
  %65 = mul nuw i64 %40, 2701098093
  %66 = add nuw i64 %65, %63
  %67 = add nuw i64 %66, %64
  %68 = zext i32 %31 to i64
  %69 = lshr i64 %67, 32
  %70 = mul nuw i64 %40, 4105433440
  %71 = add nuw i64 %70, %68
  %72 = add nuw i64 %71, %69
  %73 = zext i32 %30 to i64
  %74 = mul nuw nsw i64 %40, 1378773966
  %75 = lshr i64 %72, 32
  %76 = add nuw nsw i64 %74, %73
  %77 = add nuw nsw i64 %76, %75
  %78 = zext i32 %29 to i64
  %79 = lshr i64 %77, 32
  %80 = mul nuw nsw i64 %40, 419427594
  %81 = add nuw nsw i64 %80, %78
  %82 = add nuw nsw i64 %81, %79
  %83 = zext i32 %28 to i64
  %84 = lshr i64 %82, 32
  %85 = mul nuw i64 %40, 4081431994
  %86 = add nuw i64 %85, %83
  %87 = add nuw i64 %86, %84
  %88 = zext i32 %27 to i64
  %89 = lshr i64 %87, 32
  %90 = mul nuw i64 %40, 2174504927
  %91 = add nuw i64 %90, %88
  %92 = add nuw i64 %91, %89
  %93 = lshr i64 %92, 32
  %94 = mul nuw i64 %40, 3761484516
  %95 = zext i32 %26 to i64
  %96 = add nuw i64 %94, %95
  %97 = add nuw i64 %96, %93
  %98 = zext i32 %25 to i64
  %99 = mul nuw i64 %40, 3898812312
  %100 = zext i32 %24 to i64
  %101 = lshr i64 %97, 32
  %102 = add nuw i64 %99, %98
  %103 = add nuw i64 %102, %101
  %104 = lshr i64 %103, 32
  %105 = mul nuw i64 %40, 2772149974
  %106 = add nuw i64 %105, %100
  %107 = add nuw i64 %106, %104
  %108 = zext i32 %23 to i64
  %109 = lshr i64 %107, 32
  %110 = mul nuw i64 %40, 2833348992
  %111 = add nuw i64 %110, %108
  %112 = add nuw i64 %111, %109
  %113 = zext i32 %22 to i64
  %114 = lshr i64 %112, 32
  %115 = zext i32 %21 to i64
  %116 = mul nuw nsw i64 %40, 1081772871
  %117 = add nuw nsw i64 %116, %113
  %118 = add nuw nsw i64 %117, %114
  %119 = lshr i64 %118, 32
  %120 = mul nuw i64 %40, 3506354860
  %121 = add nuw i64 %120, %115
  %122 = add nuw i64 %121, %119
  %123 = zext i32 %20 to i64
  %124 = mul nuw i64 %40, 3987999635
  %125 = lshr i64 %122, 32
  %126 = zext i32 %19 to i64
  %127 = add nuw i64 %124, %123
  %128 = add nuw i64 %127, %125
  %129 = lshr i64 %128, 32
  %130 = mul nuw i64 %40, 2627469643
  %131 = add nuw i64 %130, %126
  %132 = add nuw i64 %131, %129
  %133 = lshr i64 %132, 32
  %134 = mul nuw nsw i64 %40, 1604188433
  %135 = zext i32 %18 to i64
  %136 = add nuw nsw i64 %134, %135
  %137 = add nuw nsw i64 %136, %133
  %138 = zext i32 %17 to i64
  %139 = mul nuw i64 %40, 2249532369
  %140 = lshr i64 %137, 32
  %141 = zext i32 %16 to i64
  %142 = add nuw i64 %139, %138
  %143 = add nuw i64 %142, %140
  %144 = zext i32 %15 to i64
  %145 = mul nuw nsw i64 %40, 1345299701
  %146 = lshr i64 %143, 32
  %147 = add nuw nsw i64 %145, %141
  %148 = add nuw nsw i64 %147, %146
  %149 = lshr i64 %148, 32
  %150 = mul nuw i64 %40, 3823538910
  %151 = add nuw i64 %150, %144
  %152 = add nuw i64 %151, %149
  %153 = zext i32 %14 to i64
  %154 = mul nuw i64 %40, 4154587822
  %155 = lshr i64 %152, 32
  %156 = zext i32 %13 to i64
  %157 = add nuw i64 %154, %156
  %158 = add nuw i64 %157, %155
  %159 = lshr i64 %158, 32
  %160 = mul nuw nsw i64 %40, 1375593148
  %161 = add nuw nsw i64 %160, %153
  %162 = add nuw nsw i64 %161, %159
  %163 = zext i32 %12 to i64
  %164 = lshr i64 %162, 32
  %165 = zext i32 %11 to i64
  %166 = mul nuw nsw i64 %40, 98324925
  %167 = add nuw nsw i64 %166, %163
  %168 = add nuw nsw i64 %167, %164
  %169 = lshr i64 %168, 32
  %170 = mul nuw nsw i64 %40, 1531966852
  %171 = add nuw nsw i64 %170, %165
  %172 = add nuw nsw i64 %171, %169
  %173 = zext i32 %10 to i64
  %174 = mul nuw nsw i64 %40, 693020143
  %175 = lshr i64 %172, 32
  %176 = add nuw nsw i64 %174, %173
  %177 = add nuw nsw i64 %176, %175
  %178 = zext i32 %9 to i64
  %179 = zext i32 %8 to i64
  %180 = mul nuw nsw i64 %40, 393246881
  %181 = lshr i64 %177, 32
  %182 = add nuw nsw i64 %180, %178
  %183 = add nuw nsw i64 %182, %181
  %184 = zext i32 %7 to i64
  %185 = mul nuw i64 %40, 2638282284
  %186 = lshr i64 %183, 32
  %187 = add nuw i64 %185, %179
  %188 = add nuw i64 %187, %186
  %189 = lshr i64 %188, 32
  %190 = zext i32 %6 to i64
  %191 = mul nuw i64 %40, 2558212184
  %192 = add nuw i64 %191, %184
  %193 = add nuw i64 %192, %189
  %194 = and i64 %43, 4294967295
  %195 = lshr i64 %193, 32
  %196 = mul nuw nsw i64 %40, 10918034
  %197 = add nuw nsw i64 %196, %190
  %198 = add nuw nsw i64 %197, %195
  %199 = mul i64 %43, 3435897093
  %200 = and i64 %199, 4294967295
  %201 = lshr i64 %198, 32
  %202 = mul nuw nsw i64 %200, 1217854515
  %203 = add nuw nsw i64 %202, %194
  %204 = lshr i64 %203, 32
  %205 = and i64 %48, 4294967295
  %206 = mul nuw i64 %200, 2753060553
  %207 = add nuw i64 %205, %206
  %208 = add nuw i64 %207, %204
  %209 = and i64 %52, 4294967295
  %210 = trunc i64 %208 to i32
  store i32 %210, ptr %412, align 1
  %211 = lshr i64 %208, 32
  %212 = mul nuw nsw i64 %200, 629029526
  %213 = add nuw nsw i64 %209, %212
  %214 = add nuw nsw i64 %213, %211
  %215 = trunc i64 %214 to i32
  store i32 %215, ptr %411, align 1
  %216 = mul nuw i64 %200, 2425356920
  %217 = and i64 %57, 4294967295
  %218 = lshr i64 %214, 32
  %219 = add nuw i64 %217, %216
  %220 = add nuw i64 %219, %218
  %221 = trunc i64 %220 to i32
  store i32 %221, ptr %413, align 1
  %222 = and i64 %67, 4294967295
  %223 = lshr i64 %220, 32
  %224 = and i64 %62, 4294967295
  %225 = mul nuw i64 %200, 2517102993
  %226 = add nuw i64 %224, %225
  %227 = add nuw i64 %226, %223
  %228 = trunc i64 %227 to i32
  store i32 %228, ptr %414, align 1
  %229 = lshr i64 %227, 32
  %230 = mul nuw nsw i64 %200, 1475365766
  %231 = add nuw nsw i64 %222, %230
  %232 = add nuw nsw i64 %231, %229
  %233 = and i64 %72, 4294967295
  %234 = trunc i64 %232 to i32
  store i32 %234, ptr %415, align 1
  %235 = lshr i64 %232, 32
  %236 = mul nuw nsw i64 %200, 136727548
  %237 = add nuw nsw i64 %233, %236
  %238 = add nuw nsw i64 %237, %235
  %239 = trunc i64 %238 to i32
  store i32 %239, ptr %416, align 1
  %240 = lshr i64 %238, 32
  %241 = and i64 %77, 4294967295
  %242 = mul nuw i64 %200, 4233887183
  %243 = add nuw i64 %241, %242
  %244 = add nuw i64 %243, %240
  %245 = trunc i64 %244 to i32
  store i32 %245, ptr %417, align 1
  %246 = mul nuw i64 %200, 2255331200
  %247 = lshr i64 %244, 32
  %248 = and i64 %82, 4294967295
  %249 = add nuw i64 %248, %246
  %250 = add nuw i64 %249, %247
  %251 = and i64 %87, 4294967295
  %252 = trunc i64 %250 to i32
  store i32 %252, ptr %418, align 1
  %253 = lshr i64 %250, 32
  %254 = mul nuw nsw i64 %200, 1492015397
  %255 = add nuw nsw i64 %251, %254
  %256 = add nuw nsw i64 %255, %253
  %257 = trunc i64 %256 to i32
  store i32 %257, ptr %419, align 1
  %258 = mul nuw i64 %200, 4023301900
  %259 = lshr i64 %256, 32
  %260 = and i64 %92, 4294967295
  %261 = add nuw i64 %260, %258
  %262 = add nuw i64 %261, %259
  %263 = and i64 %97, 4294967295
  %264 = trunc i64 %262 to i32
  store i32 %264, ptr %420, align 1
  %265 = mul nuw nsw i64 %200, 897411295
  %266 = and i64 %103, 4294967295
  %267 = lshr i64 %262, 32
  %268 = add nuw nsw i64 %263, %265
  %269 = add nuw nsw i64 %268, %267
  %270 = mul nuw nsw i64 %200, 370872652
  %271 = trunc i64 %269 to i32
  store i32 %271, ptr %421, align 1
  %272 = and i64 %107, 4294967295
  %273 = lshr i64 %269, 32
  %274 = add nuw nsw i64 %266, %270
  %275 = add nuw nsw i64 %274, %273
  %276 = trunc i64 %275 to i32
  store i32 %276, ptr %422, align 1
  %277 = mul nuw nsw i64 %200, 428547293
  %278 = lshr i64 %275, 32
  %279 = add nuw nsw i64 %272, %277
  %280 = add nuw nsw i64 %279, %278
  %281 = trunc i64 %280 to i32
  store i32 %281, ptr %423, align 1
  %282 = lshr i64 %280, 32
  %283 = and i64 %112, 4294967295
  %284 = mul nuw i64 %200, 2593242090
  %285 = add nuw i64 %283, %284
  %286 = add nuw i64 %285, %282
  %287 = mul nuw nsw i64 %200, 1716368011
  %288 = and i64 %118, 4294967295
  %289 = trunc i64 %286 to i32
  store i32 %289, ptr %424, align 1
  %290 = lshr i64 %286, 32
  %291 = add nuw nsw i64 %288, %287
  %292 = add nuw nsw i64 %291, %290
  %293 = trunc i64 %292 to i32
  store i32 %293, ptr %425, align 1
  %294 = mul nuw i64 %200, 3628350484
  %295 = lshr i64 %292, 32
  %296 = mul nuw i64 %200, 3766481658
  %297 = and i64 %122, 4294967295
  %298 = add nuw i64 %297, %294
  %299 = add nuw i64 %298, %295
  %300 = trunc i64 %299 to i32
  store i32 %300, ptr %426, align 1
  %301 = and i64 %128, 4294967295
  %302 = lshr i64 %299, 32
  %303 = add nuw i64 %301, %296
  %304 = add nuw i64 %303, %302
  %305 = trunc i64 %304 to i32
  store i32 %305, ptr %427, align 1
  %306 = lshr i64 %304, 32
  %307 = and i64 %132, 4294967295
  %308 = mul nuw i64 %200, 2214505236
  %309 = add nuw i64 %307, %308
  %310 = add nuw i64 %309, %306
  %311 = mul nuw nsw i64 %200, 748792706
  %312 = and i64 %137, 4294967295
  %313 = trunc i64 %310 to i32
  store i32 %313, ptr %428, align 1
  %314 = lshr i64 %310, 32
  %315 = add nuw nsw i64 %312, %311
  %316 = add nuw nsw i64 %315, %314
  %317 = trunc i64 %316 to i32
  store i32 %317, ptr %429, align 1
  %318 = and i64 %143, 4294967295
  %319 = mul nuw i64 %200, 2321633969
  %320 = lshr i64 %316, 32
  %321 = add nuw i64 %318, %319
  %322 = add nuw i64 %321, %320
  %323 = and i64 %148, 4294967295
  %324 = trunc i64 %322 to i32
  store i32 %324, ptr %430, align 1
  %325 = lshr i64 %322, 32
  %326 = mul nuw nsw i64 %200, 172068792
  %327 = add nuw nsw i64 %323, %326
  %328 = add nuw nsw i64 %327, %325
  %329 = trunc i64 %328 to i32
  store i32 %329, ptr %431, align 1
  %330 = lshr i64 %328, 32
  %331 = and i64 %152, 4294967295
  %332 = mul nuw i64 %200, 3404311026
  %333 = add nuw i64 %331, %332
  %334 = add nuw i64 %333, %330
  %335 = mul nuw nsw i64 %200, 414718791
  %336 = trunc i64 %334 to i32
  store i32 %336, ptr %432, align 1
  %337 = and i64 %158, 4294967295
  %338 = add nuw nsw i64 %337, %335
  %339 = lshr i64 %334, 32
  %340 = add nuw nsw i64 %338, %339
  %341 = and i64 %162, 4294967295
  %342 = trunc i64 %340 to i32
  store i32 %342, ptr %433, align 1
  %343 = lshr i64 %340, 32
  %344 = mul nuw nsw i64 %200, 1939455265
  %345 = add nuw nsw i64 %341, %344
  %346 = add nuw nsw i64 %345, %343
  %347 = and i64 %168, 4294967295
  %348 = trunc i64 %346 to i32
  store i32 %348, ptr %435, align 1
  %349 = lshr i64 %346, 32
  %350 = mul nuw nsw i64 %200, 1213195057
  %351 = add nuw nsw i64 %347, %350
  %352 = add nuw nsw i64 %351, %349
  %353 = trunc i64 %352 to i32
  store i32 %353, ptr %434, align 1
  %354 = and i64 %172, 4294967295
  %355 = mul nuw i64 %200, 2245665498
  %356 = lshr i64 %352, 32
  %357 = add nuw i64 %354, %355
  %358 = add nuw i64 %357, %356
  %359 = mul nuw i64 %200, 3220407171
  %360 = trunc i64 %358 to i32
  store i32 %360, ptr %436, align 1
  %361 = and i64 %177, 4294967295
  %362 = lshr i64 %358, 32
  %363 = add nuw i64 %361, %359
  %364 = add nuw i64 %363, %362
  %365 = trunc i64 %364 to i32
  store i32 %365, ptr %437, align 1
  %366 = lshr i64 %364, 32
  %367 = and i64 %183, 4294967295
  %368 = mul nuw i64 %200, 3975143816
  %369 = add nuw i64 %367, %368
  %370 = add nuw i64 %369, %366
  %371 = and i64 %188, 4294967295
  %372 = trunc i64 %370 to i32
  store i32 %372, ptr %410, align 1
  %373 = lshr i64 %370, 32
  %374 = mul nuw nsw i64 %200, 1238332515
  %375 = add nuw nsw i64 %371, %374
  %376 = add nuw nsw i64 %375, %373
  %377 = and i64 %193, 4294967295
  %378 = trunc i64 %376 to i32
  store i32 %378, ptr %438, align 1
  %379 = lshr i64 %376, 32
  %380 = mul nuw nsw i64 %200, 1640274799
  %381 = add nuw nsw i64 %377, %380
  %382 = add nuw nsw i64 %381, %379
  %383 = trunc i64 %382 to i32
  store i32 %383, ptr %439, align 1
  %384 = lshr i64 %382, 32
  %385 = mul nuw i64 %200, 2656700081
  %386 = and i64 %198, 4294967295
  %387 = add nuw i64 %386, %385
  %388 = add nuw i64 %387, %384
  %389 = trunc i64 %388 to i32
  store i32 %389, ptr %440, align 1
  %390 = lshr i64 %388, 32
  %391 = add nuw nsw i64 %390, %201
  %392 = trunc nuw i64 %391 to i32
  store i32 %392, ptr %441, align 1
  %393 = load i32, ptr %442, align 1
  %394 = tail call i32 @llvm.bswap.i32(i32 %393)
  br label %handler_0x221109d10e6faffe.i

handler_0xa1a610b3a4c8df8d.i:                     ; preds = %entry
  %395 = getelementptr i8, ptr %vsp, i64 -24
  store i64 %4, ptr %395, align 1
  store i64 -924774522481065134, ptr %3, align 1
  %396 = getelementptr i8, ptr %vsp, i64 -56
  store i64 %4, ptr %396, align 1
  %397 = getelementptr i8, ptr %vsp, i64 -48
  store i64 0, ptr %397, align 1
  %398 = getelementptr i8, ptr %vsp, i64 -32
  %399 = getelementptr i8, ptr %vsp, i64 -72
  store i64 %arg0, ptr %399, align 1
  %400 = getelementptr i8, ptr %vsp, i64 -80
  store i64 %arg1, ptr %400, align 1
  %401 = getelementptr i8, ptr %vsp, i64 -104
  tail call void @llvm.memset.p0.i64(ptr noundef nonnull align 1 dereferenceable(24) %401, i8 0, i64 24, i1 false)
  %402 = getelementptr i8, ptr %vsp, i64 -120
  store i64 7517013216, ptr %402, align 1
  %403 = getelementptr i8, ptr %vsp, i64 -112
  store i32 0, ptr %403, align 1
  %404 = getelementptr i8, ptr %vsp, i64 -160
  %405 = inttoptr i64 %4 to ptr
  tail call void @llvm.memset.inline.p0.i64(ptr nonnull align 8 %405, i8 0, i64 128, i1 false)
  %406 = inttoptr i64 %arg1 to ptr
  %407 = getelementptr i8, ptr %406, i64 124
  %408 = load i32, ptr %407, align 1
  store i32 0, ptr %398, align 1
  store i64 -2393810276353020754, ptr %404, align 1
  %409 = tail call i32 @llvm.bswap.i32(i32 %408)
  %410 = inttoptr i64 %4 to ptr
  %411 = getelementptr i8, ptr %410, i64 60
  %412 = getelementptr i8, ptr %410, i64 24
  %413 = getelementptr i8, ptr %410, i64 84
  %414 = getelementptr i8, ptr %410, i64 64
  %415 = getelementptr i8, ptr %410, i64 108
  %416 = getelementptr i8, ptr %410, i64 16
  %417 = getelementptr i8, ptr %410, i64 4
  %418 = getelementptr i8, ptr %410, i64 28
  %419 = getelementptr i8, ptr %410, i64 96
  %420 = getelementptr i8, ptr %410, i64 44
  %421 = getelementptr i8, ptr %410, i64 92
  %422 = getelementptr i8, ptr %410, i64 76
  %423 = getelementptr i8, ptr %410, i64 52
  %424 = getelementptr i8, ptr %410, i64 12
  %425 = getelementptr i8, ptr %410, i64 88
  %426 = getelementptr i8, ptr %410, i64 48
  %427 = getelementptr i8, ptr %410, i64 80
  %428 = getelementptr i8, ptr %410, i64 104
  %429 = getelementptr i8, ptr %410, i64 32
  %430 = getelementptr i8, ptr %410, i64 124
  %431 = getelementptr i8, ptr %410, i64 8
  %432 = getelementptr i8, ptr %410, i64 72
  %433 = getelementptr i8, ptr %410, i64 36
  %434 = getelementptr i8, ptr %410, i64 68
  %435 = getelementptr i8, ptr %410, i64 112
  %436 = getelementptr i8, ptr %410, i64 100
  %437 = getelementptr i8, ptr %410, i64 116
  %438 = getelementptr i8, ptr %410, i64 120
  %439 = getelementptr i8, ptr %410, i64 40
  %440 = getelementptr i8, ptr %410, i64 56
  %441 = getelementptr i8, ptr %410, i64 20
  %442 = getelementptr i8, ptr inttoptr (i64 120 to ptr), i64 %arg1
  %.pre = load i32, ptr %411, align 1
  %.pre270 = load i32, ptr %412, align 1
  %.pre271 = load i32, ptr %413, align 1
  %.pre272 = load i32, ptr %414, align 1
  %.pre273 = load i32, ptr %415, align 1
  %.pre274 = load i32, ptr %416, align 1
  %.pre275 = load i32, ptr %417, align 1
  %.pre276 = load i32, ptr %418, align 1
  %.pre277 = load i32, ptr %419, align 1
  %.pre278 = load i32, ptr %420, align 1
  %.pre279 = load i32, ptr %421, align 1
  %.pre280 = load i32, ptr %422, align 1
  %.pre281 = load i32, ptr %423, align 1
  %.pre282 = load i32, ptr %424, align 1
  %.pre283 = load i32, ptr %425, align 1
  %.pre284 = load i32, ptr %426, align 1
  %.pre285 = load i32, ptr %427, align 1
  %.pre286 = load i32, ptr %428, align 1
  %.pre287 = load i32, ptr %429, align 1
  %.pre288 = load i32, ptr %430, align 1
  %.pre289 = load i32, ptr %431, align 1
  %.pre290 = load i32, ptr %432, align 1
  %.pre291 = load i32, ptr %433, align 1
  %.pre292 = load i32, ptr %434, align 1
  %.pre293 = load i32, ptr %435, align 1
  %.pre294 = load i32, ptr %436, align 1
  %.pre295 = load i32, ptr %437, align 1
  %.pre296 = load i32, ptr %410, align 1
  %.pre297 = load i32, ptr %438, align 1
  %.pre298 = load i32, ptr %439, align 1
  %.pre299 = load i32, ptr %440, align 1
  %.pre300 = load i32, ptr %441, align 1
  br label %handler_0x221109d10e6faffe.i

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
