VPVM 取扱説明書
===============

VPVM とは
---------

VPVM は MikuMikuDance (以下 MMD) [1] の互換実装 [2] として作られた MMDAgent [3] から派生したアプリケーションです。

歴史的経緯として最初に MMDAgent を Windows 以外に対応させたアプリケーションとして MMDAI が作成され、その後 MMDAI で使われていたライブラリを土台に MMD のクローンとして MMDAI2 が公開されました。これを再設計して実装したものが VPVM となります。

VPVM は MMD と異なり、Windows 以外の OS で動くように設計されています。VPVM は簡単に言うと以下のことが出来ます。

-   PMD [4] / PMX [5] / X [6] 形式のモデルの読み込み
-   ポーズ (VPD [7]) 含む VMD [8] /MVD [9] 形式のモーションの読み込み、再生、編集及び保存
-   動画形式での出力

> **note**
>
> PMX 形式は現時点でバージョン 2.0 が読み込み可能ですが、SDEF 変形に対応していないため BDEF2 で変形します。

VPVM は以下のことが出来ません。

-   PMM [10] 形式のプロジェクトの読み込み
-   PMD/PMX 形式のモデルの編集及び保存
-   MikuMikuEffect (以下 MME) [11] で採用されている HLSL [12] 形式のエフェクトの読み込み（要は MME 互換）

VPVM は互換実装という位置づけのため、以下の実装が正しく機能しないことがあります

-   物理演算 [13]
-   IK [14]

VPVM は MMDAgent と同じく３条項 BSD ライセンス（別名修正 BSD ライセンスと呼ばれる） [15] を採用したオープンソースのソフトウェアとして公開されており、github [16] 上でソースコードを見ることが出来ます。

VPVM のインターフェース
-----------------------

VPVM のインターフェースは大きく分けて３つに分けられます。

[VPVMの画面]()

### タイムライン

モデルのボーン及びモーフを選択したり、キーフレームを登録したり削除したりするために使われます。画面左上にあります。

### プレビュー

モデルを表示する画面です。画面右側にあります。

### プロパティタブ (下半分)

タイムラインまたはモデルを数値で操作したり設定するための画面です。画面下にあります。

ここではそれぞれの詳しい説明をします。

タイムライン
------------

VPVM の立ち上げ時はモデル及びモーションが何もない状態となります。この時タイムラインにモデルの読み込みを促す説明が表示されるので、以下の操作をすることによってこの状態から遷移する事が出来ます。

-   メニューの「ファイル」「モデルを読み込む」からモデルを読み込む
-   タイムラインをクリックする

前者を実行してファイルダイアログを開いて確認ダイアログに同意すると、そのモデルが選択されてタイムライン上で空のモーションが作成された状態で読み込まれてモーション編集画面に移動します。

後者を実行すると一旦モデル選択画面に遷移します。この時「モデルまたはアクセサリを追加する」を選択すると前者と同じように行われます。また、モデル以外にも「カメラ」及び「光源」が選択可能です。それらを選択した場合はそれぞれのモーション編集画面に移動します。

### モーション編集

モーション編集画面ではモデルのボーン及びモーフ名のカテゴリ名が表示されます。

カテゴリ名をクリックすることによってカテゴリ以下が展開されてその中のボーン名またはモーフ名をクリックすることによって対応するボーン及びモーフを選択することが出来ます。

この状態でボーンまたはモーフを動かすことによって現在位置のボーンまたはモーフに対して自動的にキーフレームが登録されます。

#### 現在位置を移動させるには

タイムラインの縦長の赤い線は現在位置となっており、これをドラッグするか、あるいは時間の表示部分にクリックすると現在位置を移動させることが出来ます。この機能はプロパティタブの「時間及び現在位置の設定」の「再生位置」と同一です。

#### タイムラインを伸縮させるには

また、タイムラインの左下のボタンはタイムラインのサスペンダーとなっており、タイムラインの拡縮を行うことが出来ます。右側に移動させると縮小され、左側に移動させると拡大することが出来ます。この機能はプロパティタブの「時間及び現在位置の設定」の「拡大率」と同一です。

モーション編集画面では左上に４つのボタンがあり、左から順に「モデル選択画面の移動」、「プレビューの再生」、「プレビューの一時停止」、「プレビューの停止」の機能を持ちます。

#### プレビューの再生

プレビューを再生します。プレビュー再生中はモーション編集及びプロパティタブの操作が不可能になります。

#### プレビューの一時停止

再生中のプレビューを一時停止します。再度再生する場合は「プレビューの再生」を選択することによって一時停止した場所から再生します。

#### プレビューの停止

再生中のプレビューを停止して現在位置を 0 に強制的に移動させます。

> **note**
>
> 動画書き出し時にエンコード中状態に入った場合はエンコードをキャンセルする機能に変化します。

#### モデル選択画面の移動するには

モデル選択画面に遷移し、別のモデル、カメラまたは光源のモーション編集に移動する事ができます。遷移前のモデルが選択された場合は遷移前のモデルのボーン及びモーフの選択状態が復元されます。

プレビュー
----------

プレビューはモデルやアクセサリが読み込まれた後に表示される部分です。プレビュー画面は４隅にアイコンまたはテキストが配置されます。

### 左上

上から選択中のモデル名、ボーン名、モーフ名が表示されます。選択されていない場合は（なし）で表示されます。

### 左下

FPS [17] とタイムラインの表示非表示を切り替えるボタンが表示されます。

### 右上

左側の虫眼鏡のアイコンがカメラの拡大縮小を、右側の４方向の十字アイコンがカメラの移動を示します。

### 右下

上はメニューの「モデル」「ボーン」「変形モード」と同様。クリックすることで Local =\> Global =\> View と切り替えることが出来ます。真ん中の十字方向のアイコンはボーンの移動、下の回転アイコンはボーンの回転をそれぞれ指します。ボーンが操作可能の場合は 左から X,Y,Z の順で赤緑青で色付けされます。操作不可能の場合は灰色で色付けされます。

プロパティタブ
--------------

プロパティは５つの項目で分類されます。

- モデル
- カメラ
- 照明
- タイムライン
- 書き出し

### モデルタブ

モデルタブは一番左側にある「タイプ」によって以下３つのモードに切り替えることが出来ます。

- モデル
- ボーン
- モーフ

モデルタブはモデルまたはアクセサリの読み込み後に自動的に選択されます。モデルタブはアクセサリも同じ設定を利用するため、モデルタブにおいてアクセサリもモデルとみなします。

#### プロパティ

##### 拡大率  

モデルの拡大率を変更します。MMD との互換性をとるためモデルには 1.0 が、アクセサリには 10.0 がそれぞれ初期値に設定されます。

##### 不透明度  

モデルの不透明度を変更します。0.0 にすると完全に透過（＝非表示と同じ）されます。初期値は 1.0 が設定されます。

##### エッジ  

エッジ [18] 幅を設定します。最大値である 2.0 にすると極太のエッジが表示され、0.0 にするとエッジが全く表示されなくなります。初期値は 1.0 が設定されます。

##### 表示  

モデルを表示するかを切り替えます。チェックを外すとモデルが非表示になります。

##### 接続先親

現在選択されているモデルを他のモデルのボーンに追従するためのモデル及びボーンを選択します。親となるモデルとボーンを選択すると現在選択されているモデルがその親のモデルのボーンに対して動きを追従するようになります。

##### 移動量

モデルの基準移動量を設定します。これはモデルのボーンとは全く関係ない独立した値であり、プロジェクト内でのみ有効です。そのため、モーションファイルに保存時にも反映させる場合はモデルの「全ての親」[19] ボーンを利用する必要があります。

##### 回転量

モデルの基準回転量を設定します。上記の「移動量」と同様にモデルのボーンとは全く関係ない独立した値であり、プロジェクト内でのみ有効です。そのため、モーションファイルに保存時にも反映させる場合はモデルの「全ての親」ボーンを利用する必要があります。

### ボーン (ボーンモード)

#### モデル

モデルの編集モードを指定します。編集モードは以下の３つが利用可能です。「移動」で移動用のギズモが、「回転」で回転用のギズモがそれぞれ表示されます。

> **note**
>
> 移動及び回転のギズモで行った変形は右下のアイコンで操作した場合と結果が異なる場合があります（特にローカル軸変形）。

##### 選択  

現在選択中のモデルに対してボーンの接続情報を示すワイヤー表示が行われ、ボーンに対してクリックすると選択可能になります。ワイヤー表示の赤色が「現在選択中のボーン」、青色が「未選択のボーン」、黄色が「IKボーン」、紫色が「固定軸のボーン（捻りボーン）」をそれぞれ表します。

##### 移動  

移動用のギズモが表示され、そのギズモを用いてボーンを移動させることが出来ます。ボーンが移動不可能の場合選択できません。「スナップ付きのギズモを有効にする」を有効にすると一定の間隔で自動的にスナップが行われて補正されます。

##### 回転  

回転用のギズモが表示され、そのギズモを用いてボーンを回転させることが出来ます。ボーンが回転不可能の場合選択できません。

#### 移動用のギズモ

移動用のギズモは上記のモデル編集の「移動」を選択すると赤、緑、青の3軸の矢印と黄色の3面が表示されます。カーソルを移動させて表示が白くなった時にクリックしてドラッグすることによってボーンを移動させることが出来ます。

||説明|
|---|---|
|赤色の矢印|X軸の固定方向で移動します。|
|緑色の矢印|Y軸の固定方向で移動します。|
|青色の矢印|Z軸の固定方向で移動します。|
|黄色い面|XY/XZ/YZ の固定方向で移動します（選択した面によって異なる）。|

#### 回転用のギズモ

回転用のギズモは上記のモデル編集の「回転」を選択すると赤、緑、青の3軸のサークルと紫のサークルの4つが表示されます。カーソルを移動させて表示が黄色くなった時にクリックしてドラッグすることによってボーンを回転させることが出来ます。

||説明|
|---|---|
|赤色のサークル|X軸を中心にした回転を行います。|
|緑色のサークル|Y軸を中心にした回転を行います。|
|青色のサークル|Z軸を中心にした回転を行います。|
|紫色のサークル|カメラの視点から中心に向かう軸を中心にした回転を行います。|

#### 補間

登録されている２つのキーフレーム（適用されるのは前者のキーフレーム）の間のボーンの移動量及び回転量の補間を設定します。これを正しく用いることによって、モーションの緩急を表現したり、キーフレームの登録数を減らすことが可能です。

> **caution**
>
> 補間は例外的にキーフレームに自動登録されないため、キーフレームに反映させるには「適用」をクリックする必要があります。

X1 と Y1 が現在選択中のキーフレームの開始基準値、X2 と Y2 が次のキーフレームの終端基準値を示します。初期値は (20, 20, 107, 107) が設定され、0 から 127 の間で設定可能です。タイプは以下の４つから選択可能です。

- X 軸
- Y 軸
- Z 軸
- 回転

設定がない場合は左側の補間グラフが示す通り線形補間で処理されます。

#### 移動量

選択中のボーンの移動量を数値で直接操作します。移動モードが選択されている場合のみ表示されます。

#### 回転量

選択中のボーンの回転量を数値で直接操作します。回転モードが選択されている場合のみ表示されます。

#### 変形指定

変形方法を指定します。変形は「グローバル」、「ローカル」、「ビュー」の３つがあります。

##### グローバル  

親子関係に依存しない変形を行います。主に位置を調整するときに使用します。

##### ローカル  

 親子関係に考慮した変形を行います。以下の条件を満たす場合は独自のローカル軸が適用されます。  

- PMX モデルでボーンに対してローカル変形が指定されている場合
- PMD モデルでボーン名の後ろに「指」、「腕」、「ひじ」、「手首」がマッチする場合

> **note**
>
> 独自のローカル軸が適用されるのはプレビュー画面右下のアイコンで操作されている場合のみです。ギズモから操作している場合は適用されません。

##### ビュー  

カメラ視点からの変形を行います。

### モーフ（モーフモード）

モーフモードは左側のプルダウンにモーフのカテゴリ、右側のプルダウンにカテゴリ内の全てのモーフが表示されます。左側のモーフのカテゴリを選択すると右側の モーフ一覧が自動的に構築されます。モーフ一覧からモーフを選択すると下のスライダーが操作可能になり、そのモーフをスライダーで変形させることが出来ます。

### カメラタブ

カメラタブはモデル選択画面のカメラを選択すると自動的に選択されます。

#### 目標点

カメラが写す先となる点の位置を数値で設定します。初期値として (0.0, 10.0, 0.0) が設定されます。

#### アングル

カメラの角度を数値で設定します。数値は角度として解釈されます。初期値として (0.0, 0.0, 0.0) が設定されます。

#### 視点

視点は「視野角」と「距離」の２つの項目を設定します。

||説明|
|---|---|
|視野角|カメラの視野角を数値で設定します。初期値として 27 が設定されます。|
|距離|カメラの目標点からカメラそのものの現在位置の距離を数値で設定します。初期値として 50 が設定されます。|

#### 補間

機能的にはボーンタブにある「補間」と同じですが、カメラの特性上選択可能なタイプが２つ追加されます。また、回転が「アングル」に変更されます。

- 距離
- 視野角

### 照明タブ

照明タブはモデル選択画面の照明を選択すると自動的に選択されます。

#### 色

照明色を数値で変更します。初期値として (0.6, 0.6, 0.6) が設定されます。

#### 方向

照明の方向を設定します。初期値として (-0.5, -1.0, -0.5) が設定され、南東にある光源から北西に向かって光る形になります

> **note**
>
> 照明位置は照明方向の逆の数値になります（初期値の場合はそれぞれの数値に -1 させることにより照明位置は 0.5, 1.0, 0.5 になる）。

### タイムラインタブ

タイムラインタブは名前の通り左上のタイムラインの設定を行います。

#### 時間及び現在位置設定

##### 時間長  

タイムラインの長さを設定します。初期値は 10 分 (= 18000 キーフレーム) が設定されます。

##### 再生位置  

タイムラインの現在位置を設定します。初期値は 0 が設定されます。

##### 拡大率  

タイムラインの拡大縮小率を設定します。1.0 にすると秒単位で拡大した状態、0.01 にすると分単位で縮小した状態で表示されます。初期値は 1.0 が設定されます。

##### 時間（時：分：秒）で表示  

これを有効にすることで「時間長」と「再生位置」がフレーム単位ではなく時間で表示されるようになります。ただし、モーションは１秒 30 フレームで計算されるため、基本的にはフレーム単位で計算したほうが正確です。初期値は無効で設定されます。

#### 範囲選択

通常はボーンまたはモーフ毎にかつ１キーフレーム毎しか選択できませんが、範囲選択を使用するとボーン及びモーフかつ範囲内にある複数のキーフレームをまとめて選択することが出来ます。

##### 開始位置  

タイムラインにおける選択開始位置をキーフレーム単位で設定します。

##### 終端位置  

タイムラインにおける選択終端位置をキーフレーム単位で設定します。

##### 表示しているトラックのみ選択  

タイムラインにおいて表示されているボーンまたはモーフのトラックのみを選択するかどうかを設定します。無効にすると非表示関係なく全てのボーンまたはモーフが選択されます。

#### 範囲再生

通常は最初のキーフレームから最後のキーフレームまでの範囲を再生しますが、範囲再生を使用するとモーションの動作確認で範囲内の一部分だけ再生することが出来ます。

##### 開始位置  

タイムラインにおける再生開始位置をキーフレーム単位で設定します。

##### 終端位置  

タイムラインにおける再生終了位置をキーフレーム単位で設定します。

##### ループ再生  

ループ再生を有効にするかどうかを設定します。

### 書き出しタブ

画像または動画を書き出しするための設定または書き出し実行を行います。

> **note**
>
> メニューにある書き出しは「書き出しタブ」の設定を利用します。そのため、書き出すパラメータを変更するには書き出しタブで設定を変更する必要があります。

#### 画像

画像ではプリセットのサイズ設定または「高さ」及び「幅」の数値直接指定の２つが利用可能です。プリセットは以下の４つの大きさが予め設定されています。いずれも 16:9 のアスペクト比となります。プリセットを無効にすると数値直接指定に変更されます。

- 360p (640x360)
- 480p (854x480)
- 720p (1280x720)
- 1080p (1920x1080)

「書き出し」ボタンをクリックすることによって現在のシーンがそのまま画像に出力されます。

> **note**
>
> 透過付きで出力することも可能ですが、その場合はグローバル設定で「透過を有効」にした上で PNG 形式で出力する必要があります（BMP 形式だと透過なしで保存される）

#### 動画

動画では「画像」の大きさ設定を利用してエンコード設定及び出力範囲を指定します。

#### カスタムエンコード設定を使用する

書き出し設定は初期値で「動画形式」が PNG かつフレーム形式が BMP で設定されますが、これにチェックを入れることで変更することが可能です。出力される動画はいずれも中間出力でそのままでは再生出来ないため、動画投稿サイトに投稿するためには H.264 などの動画形式にエンコードする必要があります。

> **warning**
>
> 動画出力はディスク消費が激しく、思わぬディスク枯渇を引き起こすため最低でも 数十GB の空き容量を確保したほうが良いです。

動画形式

|形式|説明|
|---|---|
|PNG|PNG 形式の動画で出力します。AVI の場合再生できない場合があります。|
|UtVideo RGBA|UtVideo [20] の RGBA フォーマットで圧縮して出力します。|
|UtVideo YUV422|UtVideo の YUV422 フォーマットで圧縮して出力します。|
|UtVideo YUV420|UtVideo の YUV420 フォーマットで圧縮して出力します。|

> **note**
>
> UtVideo 形式の動画を再生するには別途 UtVideo のデコーダが必要です。

フレーム形式

|形式|説明|
|---|---|
|BMP|中間保存画像形式に BMP を使用して出力します。圧縮なしで出力されるため書き出しが PNG に比べて高速な点が長所ですが、ディスク消費が大きいのが短所です。|
|PNG|中間保存画像形式に PNG を使用して出力します。圧縮して出力されるためディスク消費が PNG に比べて抑えられますが、書き出しが遅くなるのが短所です。|

#### カスタム出力範囲を使用する

出力する範囲を指定された範囲のみにして出力します。タイムラインの範囲選択及び範囲再生と同様です。

#### グリッドを含める

プロジェクト設定
----------------

プロジェクト設定はメニューの「プロジェクト」の「プロジェクト設定」から行うことが出来ます。

#### プロジェクト名

プロジェクトの名前を設定します。プロジェクト名はウィンドウのタイトルに表示されます。

#### 物理演算設定

物理演算の設定を行います。

##### 有効状態  

物理演算の有効状態を選択します。「無効」で物理演算が無効になり、「演算時のみ有効」で再生時のみ物理演算を有効にし、「常に有効」で編集時でも物理演算が有効になります。初期値は「無効」です。

##### 重力及び方向  

重力方向及び方向のパラメータを設定します。初期値は (0.0, -9.8, 0.0) です。


#### アクセラレーション設定

PMX/PMD で必要な（重い）ボーンスキニング処理に対する方法を選択するための設定を行います。そのため、PMX/PMD モデルに対してのみ有効でアクセサリに対しては何も効果を発揮しません。

|項目|説明|
|---|---|
|アクセラレーションなし|アクセラレーションなしでボーンスキニングを処理します。重いですが安定した処理を行います。|
|パラレル|CPU の並列処理でボーンスキニングを処理します。CPU 数が多いほど効果を発揮します。|
|頂点シェーダスキニング|GPU の頂点シェーダでボーンスキニングを処理します。「パラレル」よりも強力に発揮しますが、場合によってはモデル崩れが発生するかもしれません。|
|OpenCL (CPU)|OpenCL を CPU 上で利用したボーンスキニングを処理します。現時点では OSX でのみ有効です。|
|OpenCL (GPU)|OpenCL を GPU 上で利用したボーンスキニングを処理します。現時点では OSX でのみ有効です。|

上記のうち「頂点シェーダスキニング」と「OpenCL (CPU)」と「OpenCL (GPU)」は設定後にモデルを読み込みした時のみ有効です。設定以前のモデルに対しては設定前の処理を行います。また、設定を変更した後でも効果は継続します。

#### その他

##### 背景色  

シーンの背景色を変更します。「グローバル設定」の「透過ウィンドウを有効にする」を有効にすると不透明度を設定することが出来ます。

##### グリッドを表示する  

シーンのグリッドを表示するかどうかを設定します。チェックを入れると表示され、外すと表示されなくなります。

##### シャドウマップの大きさ  

シャドウマップの大きさを設定します。大きいほどジャギーが減りますがフレームレートが落ちます。小さくするとフレームレートの落ちが低減しますが、ジャギーが目立つようになります。

#### 描画順

モデル及びアクセサリの描画順を設定します。

グローバル設定
--------------

グローバル設定はメニューの「設定」から行うことが出来ます。

#### グラフィックデバイス

マシンの OpenGL の情報を表示します。

#### アプリケーション

アプリケーション全体で有効な設定を行います。

##### フォントファミリー  

フォントを設定します。フォント設定はシーン及びタイムラインのみ有効です。アプリケーション全体のフォントとして適用させる場合は「フォントファミリーを共有する」にチェックを入れて下さい。

##### エフェクトを有効にする  

エフェクトを有効にするかどうかを設定します。現在実験的な機能のため、初期値は無効です。

##### サンプル数  

シーンのアンチエイリアスで使われるサンプル数を変更します。この値が大きいほどジャギーが目立ちにくくなりますが、フレームレートが低減しやすくなります。逆にするとフレームレートの低減が起こりにくくなりますがジャギーが目立つようになります。

##### フォントファミリーを共有する  

「フォントファミリー」の設定をアプリケーション全体に対して適用するかを設定します。初期値は無効です。

##### 透過ウィンドウを有効にする  

透過ウィンドウを有効にするかどうかを設定します。有効にするとプロジェクト設定の背景色で不透明度が設定できるようになります。有効にすると描画が崩れやすくなるため、必要なときのみ使用して下さい。初期値は無効です。

#### ログ設定

ログ設定を行います。ログの保存場所とログ出力頻度を設定します。

VPVM のメニュー
---------------

### ファイル

#### 新規プロジェクト

プロジェクトを新規に作成します。

> **note**
> 
> すでにモデルまたはモーションが存在する場合、確認画面を表示して OK が押された場合にのみ全て破棄されます。

####  新規モーション

現在選択中のモデルに対してモーションを新規に作成します。

> **note**
>
> すでにモーションが割り当てられている場合、確認画面を表示して OK が押された場合にのみそのモーションは破棄されます。

#### プロジェクトを開く

作成したプロジェクトを開きます。すでにモデルやモーションがある場合は「新規プロジェクト」と同じく確認画面を表示します。

####  モデルまたはアクセサリを追加

拡張子が .pmd か .pmx 形式のモデルまたは拡張子が .x 形式のアクセサリを読み込みます。前者の場合は表示する前に（主にモデルに対する利用規約の）確認画面が表示されます。

#### エフェクトを追加する

拡張子が .glslfx 形式のエフェクトを追加します。

> **note**
>
> 現時点では「設定」の「エフェクトを有効にする」にチェックが入っていないと表示されません
>

#### 現在選択中のモデルのモーションを読み込む

選択されているモデルに対して拡張子が vmd または mvd 形式のモーションを読み込んで割り当てます。すでにモーションが割り当てられている場合の挙動は「新規モーション」と同じく確認画面を表示します。

#### カメラモーションを読み込む

カメラに対して拡張子が vmd または mvd 形式のモーションを読み込んで割り当てます。すでにモーションが割り当てられている場合の挙動は「新規モーション」と同じく確認画面を表示します。

#### ポーズを読み込む

現在選択中のモデルかつ現在の位置に対して拡張子が vpd 形式のファイルを読み込んでキーフレームを登録します。すでにキーフレームがある場合は上書きされて登録されます。

> **note**
>
> MikuMikuDance で使われるボーンのみの .vpd の他に MikuMikuMoving や PMXEditor で採用されるモーフも保存する拡張形式の .vpd にも対応します
>

#### オーディオの読み込み

拡張子が .wav でかつ中身が PCM 形式の音源を読み込みます。

#### 背景動画を設定する

拡張子が .avi または .mov 形式の動画を読み込んでシーンの背景に表示します。

> **note**
>
> 読み込み可能な動画の中身は OS に依存するため、ある OS では読み込めても他の OS では読み込めない場合があります

#### プロジェクトを保存する

プロジェクトを保存します。初回時は何処に保存するかのダイアログが表示され、二回目以降は初回時に指定されたファイル名で上書き保存されます。

#### プロジェクトを名前つけて保存

毎回何処に保存するかのダイアログが表示される点を除いて「プロジェクトを保存する」と同じです。

#### モデルモーションを保存

現在選択中のモデルのモーションを保存します。初回時は何処に保存するかのダイアログが表示され、二回目以降は初回時に指定されたファイル名で上書き保存されます。

#### 名前をつけてモデルモーションを保存

毎回何処に保存するかのダイアログが表示される点を除いて「モデルモーションを保存する」と同じです。

#### 画像を書き出す

#### 動画を書き出す

### 編集

#### キーフレームを登録

キーフレームを明示的に登録します。通常ボーンまたはモーフを動かした後に自動的に登録されます。

#### キーフレームを選択

#### キーフレームを削除

現在選択されているキーフレームを削除します。

> **note**
>
> 0番目のキーフレームは仕様上削除することが出来ません

#### ロック状態を切り替え

#### 可視状態を切り替え

#### コピー

#### ペースト

#### 反転ペースト

#### カット

#### 巻き戻し

前回の処理を巻き戻します（アンドゥ）。現在の実装では巻き戻し回数は特に制限していませんが、巻き戻し回数が多いほどメモリ消費が大きくなります。

#### やり直し

前回の処理をやり直します（リドゥ）。基本的には「巻き戻し」した後「やり直し」の結果は同じですが、例外もあります。

> **note**
>
> 処理によっては「巻き戻し」した後「やり直し」を行っても結果が一致しない場合があります。例えば複数のボーンの回転を行う IK ボーンが該当します

### プロジェクト

#### 再生

#### 一時停止

#### 停止

#### ループ再生を有効にする

#### カメラプリセット

#### カメラをリセット

現在のカメラ視点をリセットします。カメラの初期値は以下の表のとおりです。

|名前|初期値|
|---|---|
|視点|(X=0.0, Y=10.0, Z=0.0)|
|角度|(X=0.0, Y=0.0, Z=0.0)|
|視野角|27.0|
|距離|50.0|

#### 照明をリセット

現在の光源をリセットします。光源の初期値は以下の表のとおりです。

|名前|初期値|
|---|---|
|色|(R=0.6, G=0.6, B=0.6)|
|方向|(X=-0.5, Y=-1.0, Z=-0.5)|

#### 次の再生位置

#### 前の再生位置

#### プロジェクト設定

### モデル

#### ボーン

#### モーフ

#### エフェクト

#### 現在のモデルを削除

現在選択中のモデルを削除します。モーションが割り当てられている場合そのモーションも一緒に削除されます。また、削除するモデルを接続親に指定しているモデルがある場合接続親が「なし」になります。

### ウィンドウ

#### タイムラインを切り離す

右側のタイムラインウィンドウを切り離します。切り離された後閉じるボタンを押すとタイムラインウィンドウがくっついた状態に戻ります。

#### プロパティパネルの表示を切り替える

プロパティパネルの表示及び非表示を切り替えます。

### ヘルプ

#### 設定

#### VPVM について

#### Qt について

## 脚注

[1] <http://www.geocities.jp/higuchuu4/index.htm>

[2] 互換実装は数多くあるが、そのひとつ MikuMikuMoving (<https://sites.google.com/sites/mikumikumoving/>) は後ろの脚注で説明するためここに脚注をいれた。

[3] <http://mmdagent.jp/>

[4] Polygon Model Data の略で MikuMikuDance の標準モデルフォーマットのひとつ。詳細は非公開だが、リバースエンジニアリングにより互換実装はこのファイルが読み込める。

[5] Polygon Model Extended の略で PMD をさらに拡張したモデルのフォーマット。制約有りだが仕様は公開されている。2.0 と 2.1 の２つのバージョンがあり、VPVM は現時点で前者のみ対応。

[6] DirectX Mesh という DirectX 特有のモデルフォーマット。DirectX9 まではこのモデルフォーマットが読み込めたが、DirectX10 以降から読み込み機能が削除されてしまった。VPVM は assimp と呼ばれるライブラリを使って対応している。

[7] VOCALOID Pose Data の略で MikuMikuDance の標準ポーズフォーマット。PMD/VMD と異なり、テキスト形式で記述される。MikuMikuDance はボーンの情報しか保存されないが、MikuMikuMoving はさらにモーフの情報を保存する。VPVM は の略で、MikuMikuMoving と同じようにボーン及びモーフ両方共対応する。

[8] VOCALOID Motion Data の略で MikuMikuDance の標準モーションフォーマット。PMD と同じく詳細は非公開だがリバースエンジニアリングにより互換実装はこのファイルが読める。

[9] Motion Vector Data の略で、MikuMikuMoving が採用する拡張モーションフォーマット。VMD の弱点であるボーン名制限がなく、高い FPS かつ長時間のモーションを作成することが出来るように設計されている。

[10] Polygon Movie Maker の略で、MikuMikuDance のプロジェクトフォーマット。詳細は非公開。

[11] (TODO: MME のリンク)

[12] DirectX が採用するエフェクトのフォーマット。MMDAI2 はかつてこれを Cg で対応しようとしたが Cg と HLSL は完全な互換性を持っておらず、かつプロプライエタリなソフトウェアのため自分で修正出来ないという問題を抱えていた。

[13] 物理現象をシミュレートするための処理。MMD と同じく Bullet Physics (<http://bulletphysics.org>) を用いて演算しているが、採用しているバージョンが異なるため同一結果にはならない

[14] Inverse Kinematics の略で、逆運動と称される。足などで採用され、これを正しく用いると自動的に他のボーンの回転処理が計算されるためモーション作成の労力が大幅に減るが、正しく動作しなかった場合はボーン破錠が発生して修正コストが大きくなる。それ以外のボーンは Forward Kinematics こと順運動で処理される。

[15] <http://sourceforge.jp/projects/opensource/wiki/licenses%2Fnew_BSD_license>

[16] <https://github.com/hkrn/MMDAI/>

[17] Frames Per Seconds の略で、一秒間に表示されたフレーム数を指す。通常 60 FPS で維持され、下がる場合はグラフィックボードの限界を示す。

[18] モデルにつけられる輪郭であり、これをつけることによってアニメ調らしさを強調することが出来る。

[19] 名前通り全てのボーンの親で、モデルの絶対位置及び回転量を設定するために使われる。MikuMikuDance の標準モデルでは「センターボーン」が基準なため、モデル全体を移動または回転させるにはセンターバイアスの設定が必要。最近のモデルは「全ての親」ボーンが標準で入っている事が多い。

[20] 可逆圧縮形式の動画コーデックで、H.264 などの最終出力前の中間出力として使われる。
