#pragma once

const char PAGE_HTML[] PROGMEM = R"rawliteral(
<!doctype html>
<html>
<head>
  <meta charset="utf-8">
  <title>BIS V13 UI Mockup</title>
  <style>
    body {
      background: #111;
      color: #fff;
      font-family: Arial, sans-serif;
      margin: 10px;
      max-width: 900px;
    }
    h2 { margin: 6px 6px 6px 6px; font-size: 16px; }
    .control-row { 
      margin: 8px 8px 8px ; 
      padding: 5px 0px 0px 0px;
    }
    button {
      padding: 8px 16px;
      margin: 4px;
      border: none;
      border-radius: 3px;
      cursor: pointer;
      font-weight: bold;
      transition: background 0.2s;
    }
    button:disabled { opacity: 0.35; cursor: not-allowed; }
    button.default { background: #444; color: #fff; }
    button.default:hover:not(:disabled) { background: #666; }

    /* record & stop buttons – same width, vertical stack */
    .record-stop-stack {
      display: flex;
      flex-direction: column;
      justify-content: center;
      gap: 6px;
      width: 82px;
    }

    .record-stop-stack button {
      width: 82px;
      margin: 0;
      box-sizing: border-box;
      height: 40px;
      font-size: 10px;
      background: #444;
      color: #fff;
      display: flex;
      align-items: center;
      justify-content: center;
      text-align: center;
    }

button.record.active {
      background: #ff0000;
      color: #fff;
      box-shadow: 0 0 8px #ff0000;
    }
    button.record.active:hover { background: #cc0000; }
    button.record:hover:not(:disabled) { background: #666; }
    button.record.active:hover { background: #cc0000; }

    button.bank {
      width: 40px;
      height: 40px;
      padding: 0;
      margin: 2px;
      background: #333;
      color: #fff;
      font-size: 18px;
    }
    button.bank.empty { background: #222; }
    button.bank.stored { background: #ff8800; }
    button.bank.selected { background: #ffff00; color: #000; }
    button.bank.recording { background: #ff0000; }
    button.bank.overwrite-target { background: #aa00ff; color: #fff; box-shadow: 0 0 8px #aa00ff; }

    button.overwrite { background: #444; color: #fff; }
    button.overwrite.active { background: #aa00ff; color: #fff; box-shadow: 0 0 8px #aa00ff; }

    .cell {
      width: 20px;
      height: 20px;
      display: inline-block;
      margin: 1px;
      border: 1px solid #333;
      background: #222;
      cursor: pointer;
      position: relative;
      z-index: 2;
      transition: opacity 0.08s, background 0.08s;
      opacity: 0.32;
    }
    .cell.inrange { opacity: 1; }
    .cell.active { background: #ff8800 !important; }
    .cell.playhead {
      outline: 3px solid #ffff00;
      box-shadow: 0 0 6px #ffff00;
      z-index: 3;
      opacity: 1;
    }
    .value {
      display: inline-block;
      width: 50px;
      text-align: right;
      font-weight: bold;
    }
    .outled {
      width: 16px;
      height: 16px;
      border: 1px solid #555;
      background: #111;
      display: inline-block;
      margin: 2px;
      border-radius: 2px;
    }
    .outled.active {
      background: #00ff00;
      box-shadow: 0 0 5px #00ff00;
    }
    #console {
      width: 100%;
      height: 150px;
      background: #000;
      color: #0f0;
      font-family: monospace;
      font-size: 11px;
      overflow-y: auto;
      resize: vertical;
    }
    input[type=range] {
      width: 200px;
      vertical-align: middle;
    }
    input[type=range]:disabled { opacity: 0.4; cursor: not-allowed; }
    .grid-row {
      display: flex;
      margin: 2px 0;
      position: relative;
      z-index: 2;
    }
    .rangebar {
      width: 500px;
      height: 16px;
      background: #1a1a1a;
      border: 2px solid #555;
      position: relative;
      margin: 8px 0;
      border-radius: 3px;
    }
    .rangehighlight {
      position: absolute;
      background: rgba(255, 136, 0, 0.6);
      height: 100%;
      border: 1px solid #ff8800;
      box-shadow: inset 0 0 3px rgba(255, 136, 0, 0.8);
      transition: left 0.1s linear, width 0.1s linear;
    }
    #rng { font-size: 12px; color: #ff8800; font-weight: bold; }
    .bank-section {
      display: flex;
      align-items: center;
      gap: 18px;
    }

    .bank-column {
      display: flex;
      flex-direction: column;
      gap: 5px;
    }

    .bank-row {
      display: grid;
      grid-template-columns: repeat(8, 40px);
      gap: 3px;
    }

    .overwrite-wrap {
      display: flex;
      align-items: center;
      justify-content: center;
      height: 83px;
      min-width: 100px;
    }

    .overwrite-wrap button {
      margin: 0;
      height: 40px;
    }
    hr { border-color: #333; }
  </style>
</head>
<body>
<h2>BIS V13 - Behavioral Composition</h2>
<div class="control-row">
  <button class="default" id="playBtn" onclick="s('PLAY')">PLAY</button>
  <button class="default" onclick="s('STOP')">STOP</button>
</div>
<div class="control-row">
  BPM <span id=bpmv class=value>120</span>
  <input id=bpm type=range min=20 max=240 value=120 oninput="bpmv.textContent=this.value">
</div>
<div class="control-row">
  ONTIME <span id=ontv class=value>50</span>ms
  <input id=ont type=range min=10 max=1000 value=50 oninput="ontv.textContent=this.value">
</div>
<div class="control-row">
  DRUNK <span id=drv class=value>0</span>%
  <input id=dr type=range min=0 max=100 value=0 oninput="drv.textContent=this.value">
</div>
<div class="control-row">
  PROB <span id=prv class=value>100</span>%
  <input id=pr type=range min=0 max=100 value=100 oninput="prv.textContent=this.value">
</div>
<hr>
<div class="control-row" style="background:#1a1a1a;padding:8px;border-radius:3px">
  <strong>Range Navigation:</strong><br><br>
  STEPS <span id=stv class=value>25</span>
  <input id=st type=range min=1 max=25 value=25><br><br>
  SCRUB <span id=scv class=value>0</span>
  <input id=sc type=range min=0 max=24 value=0><br><br>
  <div class='rangebar'><div class='rangehighlight' id='rh'></div></div>
  <span id=rng>RANGE=0-24</span>
</div>
<hr>
<div class="control-row">
  <strong>Banks:</strong><br><br>
  <div class="bank-section">
    <div class="record-stop-stack">
      <button class="record" id="recordBtn" onclick="s('RECORD')">RECORD</button>
      <button class="stop-row" onclick="s('STOP')">STOP</button>
    </div>

    <div class="bank-column">
      <div class="bank-row" id="bankgrid"></div>
      <div class="bank-row"></div>
    </div>

    <div class="overwrite-wrap">
      <button class="overwrite" id="overwriteBtn" onclick="s('OVERWRITE')">OVERWRITE</button>
    </div>
  </div>
</div>
<hr>
<div class="control-row">
  <strong>Output Status:</strong><br><br>
  <div id='outs'></div>
</div>
<hr>
<div class="control-row">
  <strong>Sequencer Grid:</strong><br><br>
  <div id=g></div>
</div>
<hr>
<div class="control-row">
  <strong>Console:</strong><br><br>
  <textarea id='console' readonly></textarea>
</div>
<script>
  const T=7, S=25, NBKS=16;
  const g = document.getElementById('g');
  const outs = document.getElementById('outs');
  const con = document.getElementById('console');
  const bankgrid = document.getElementById('bankgrid');

  let isRecordingUI = false;
  let recordingBankUI = -1;
  let bankHasData = [];
  let selectedBankUI = -1;
  let isBankPlayingUI = false;
  let overwriteModeUI = false;
  let overwriteTargetUI = 255;

  // Output LEDs
  for (let i=0; i<T; i++) {
    let d = document.createElement('div');
    d.className = 'outled';
    d.id = 'out'+i;
    d.title = 'Track '+i;
    outs.appendChild(d);
  }

  // Grid
  for (let t=0; t<T; t++) {
    let r = document.createElement('div');
    r.className = 'grid-row';
    r.id = 'row'+t;
    for (let s=0; s<S; s++) {
      let b = document.createElement('div');
      b.className = 'cell';
      b.id = `c_${t}_${s}`;
      b.onclick = (() => { if (!isBankPlayingUI) ws.send(`S:${t}:${s}`); });
      r.appendChild(b);
    }
    g.appendChild(r);
  }

  // Bank buttons (8 per row, 2 rows)
  for (let i=0; i<NBKS; i++) {
    let btn = document.createElement('button');
    btn.className = 'bank empty';
    btn.textContent = (i+1);
    btn.id = 'bank'+i;
    btn.onclick = (() => {
      if (isRecordingUI) {
        if (recordingBankUI === i) ws.send('BANK:'+i);
        return;
      }
      if (overwriteModeUI) { ws.send('BANK:'+i); return; }
      if (bankHasData[i]) ws.send('BANK:'+i);
    });
    bankgrid.appendChild(btn);
  }

  function clearGrid() {
    document.querySelectorAll('.cell.playhead').forEach(x => x.classList.remove('playhead'));
  }

  function updateRangeHighlight() {
    let stepsVal = parseInt(st.value);
    let scrubVal = parseInt(sc.value);
    let rangeEnd = Math.min(scrubVal + stepsVal - 1, 24);
    document.querySelectorAll('.cell.inrange').forEach(x => x.classList.remove('inrange'));
    for (let s=scrubVal; s<=rangeEnd; s++) {
      for (let t=0; t<T; t++) {
        let c = document.getElementById(`c_${t}_${s}`);
        if (c) c.classList.add('inrange');
      }
    }
  }

  function flashOut(n) {
    let e = document.getElementById('out'+n);
    if (e) e.classList.add('active');
  }
  function clearOut(n) {
    let e = document.getElementById('out'+n);
    if (e) e.classList.remove('active');
  }

  function updateRangeBar() {
    let stepsVal = parseInt(st.value);
    let scrubVal = parseInt(sc.value);
    let rb = document.getElementById('rh');
    let left = (scrubVal / 25) * 100;
    let width = (stepsVal / 25) * 100;
    rb.style.left = left + '%';
    rb.style.width = width + '%';
    updateRangeHighlight();
  }

  function updateBankUI() {
    for (let i=0; i<NBKS; i++) {
      let btn = document.getElementById('bank'+i);
      if (!btn) continue;
      btn.className = 'bank ';
      if (recordingBankUI === i) { btn.className += 'recording'; }
      else if (overwriteModeUI && overwriteTargetUI === i) { btn.className += 'overwrite-target'; }
      else if (selectedBankUI === i && bankHasData[i]) { btn.className += 'selected'; }
      else if (bankHasData[i]) { btn.className += 'stored'; }
      else { btn.className += 'empty'; }
      btn.disabled = (isRecordingUI && recordingBankUI !== i);
    }
    let owBtn = document.getElementById('overwriteBtn');
    if (owBtn) {
      if (overwriteModeUI) { owBtn.classList.add('active'); }
      else { owBtn.classList.remove('active'); }
      owBtn.disabled = isRecordingUI;
    }
  }

  function updateRecordBtn() {
    let btn = document.getElementById('recordBtn');
    if (isRecordingUI) {
      btn.classList.add('active');
      btn.textContent = 'RECORDING';
    } else {
      btn.classList.remove('active');
      btn.textContent = 'RECORD';
    }
  }

  function updateControlState() {
    let isLocked = isBankPlayingUI;
    bpm.disabled = isLocked;
    ont.disabled = isLocked;
    dr.disabled = isLocked;
    pr.disabled = isLocked;
    st.disabled = isLocked;
    sc.disabled = isLocked;
    document.querySelectorAll('.cell').forEach(c => c.style.pointerEvents = isLocked ? 'none' : 'auto');
    document.getElementById('playBtn').disabled = isRecordingUI;
  }

  // WebSocket
  const ws = new WebSocket('ws://'+location.hostname+':81/');
  ws.onopen = () => {
    con.value = 'CONNECTED\n';
    updateRangeHighlight();
    updateBankUI();
    updateRecordBtn();
    updateControlState();
  };

  bpm.oninput = e => { if (!isBankPlayingUI) { bpmv.textContent = e.target.value; ws.send('BPM:'+e.target.value); } };
  ont.oninput = e => { if (!isBankPlayingUI) { ontv.textContent = e.target.value; ws.send('ONT:'+e.target.value); } };
  dr.oninput = e => { if (!isBankPlayingUI) { drv.textContent = e.target.value; ws.send('DRUNK:'+e.target.value); } };
  pr.oninput = e => { if (!isBankPlayingUI) { prv.textContent = e.target.value; ws.send('PROB:'+e.target.value); } };
  st.oninput = e => { if (!isBankPlayingUI) { stv.textContent = e.target.value; ws.send('STEPS:'+e.target.value); updateRangeBar(); } };
  sc.oninput = e => { if (!isBankPlayingUI) { scv.textContent = e.target.value; ws.send('SCRUB:'+e.target.value); updateRangeBar(); } };

  ws.onmessage = e => {
    let m = e.data;
    if (m.startsWith('LOG:')) { con.value += m.substring(4) + '\n'; con.scrollTop = con.scrollHeight; }
    if (m.startsWith('OUT:')) {
      let p = m.split(':');
      let track = Number(p[1]);
      let ontime = Number(p[2]);
      flashOut(track);
      setTimeout(() => clearOut(track), ontime);
    }
    if (m.startsWith('G:')) {
      let p = m.split(':');
      let c = document.getElementById(`c_${p[1]}_${p[2]}`);
      if (c) { if (Number(p[3])) c.classList.add('active'); else c.classList.remove('active'); }
    }
    if (m.startsWith('P:')) {
      let st = Number(m.substring(2));
      clearGrid();
      for (let t=0; t<T; t++) {
        let c = document.getElementById(`c_${t}_${st}`);
        if (c) c.classList.add('playhead');
      }
    }
    if (m.startsWith('CFG:')) {
      let p = m.split(':');
      bpm.value = p[1]; bpmv.textContent = p[1];
      ont.value = p[2]; ontv.textContent = p[2];
      dr.value = p[3]; drv.textContent = p[3];
      pr.value = p[4]; prv.textContent = p[4];
      st.value = p[5]; stv.textContent = p[5];
      sc.value = p[6]; scv.textContent = p[6];
      updateRangeBar();
    }
    if (m.startsWith('RNG:')) {
      let p = m.split(':');
      rng.textContent = 'RANGE='+p[1]+'-'+p[2];
    }
    if (m.startsWith('ANIM:')) {
      let p = m.split(':');
      bpm.value = p[1]; bpmv.textContent = p[1];
      ont.value = p[2]; ontv.textContent = p[2];
      dr.value = p[3]; drv.textContent = p[3];
      pr.value = p[4]; prv.textContent = p[4];
      st.value = p[5]; stv.textContent = p[5];
      sc.value = p[6]; scv.textContent = p[6];
      updateRangeBar();
    }
    if (m.startsWith('BANKS:')) {
      let p = m.split(':');
      let hasDataStr = p[1];
      selectedBankUI = Number(p[2]);
      isRecordingUI = (Number(p[3]) === 1);
      recordingBankUI = Number(p[4]);
      isBankPlayingUI = (Number(p[5]) === 1);
      overwriteModeUI = (Number(p[6]) === 1);
      overwriteTargetUI = Number(p[7]);
      for (let i=0; i<NBKS; i++) { bankHasData[i] = (hasDataStr[i] === '1'); }
      updateBankUI();
      updateRecordBtn();
      updateControlState();
    }
  };

  function s(x) { ws.send(x); }

  // ---- MOCK DATA ----
  for (let i=0; i<16; i++) {
    bankHasData[i] = (i < 8);
  }
  selectedBankUI = 2;
  updateBankUI();
  updateRecordBtn();
  updateControlState();
  updateRangeHighlight();
</script>
</body>
</html>)rawliteral";
