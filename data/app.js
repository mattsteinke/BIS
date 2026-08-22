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
  if (rb) {
    let left = (scrubVal / 25) * 100;
    let width = (stepsVal / 25) * 100;
    rb.style.left = left + '%';
    rb.style.width = width + '%';
  }
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
    let rngEl = document.getElementById('rng');
    if (rngEl) rngEl.textContent = 'RANGE='+p[1]+'-'+p[2];
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
