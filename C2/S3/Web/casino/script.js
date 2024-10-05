let pts = 100;
const butAdd = document.getElementById("add");
let flag = false;
butAdd.addEventListener("click", () => {
    addPts(100);
});

const butStr = document.getElementById("str")

function arrayRandElement(arr) {
    const rand = Math.floor(Math.random() * arr.length);
    return arr[rand];
}

function roll(images) {
    next = arrayRandElement(images.getElementsByClassName("hidden"));
    images.getElementsByClassName("hidden-down")[0].className = "hidden";
    images.getElementsByClassName("active-down")[0].className = "hidden-down";
    images.getElementsByClassName("active-middle")[0].className = "active-down";
    images.getElementsByClassName("active-top")[0].className = "active-middle";
    images.getElementsByClassName("hidden-top")[0].className = "active-top";
    next.className = "hidden-top";
}

function getValue(type) {
    if (type == "BAN") return 2;
    if (type == "BELL") return 2;
    if (type == "CHER") return 3;
    if (type == "JOK") return 3;
    if (type == "BAG") return 4;
    if (type == "ORG") return 4;
    if (type == "CRD") return 5;
    if (type == "RCT") return 6;
}

function countPts() {
    const images = document.getElementsByClassName("active-middle");
    let types = [0, 0, 0, 0, 0];
    let plus = 0;
    for (let i = 0; i < images.length; i++) {
        types[i] = images[i].getAttribute("alt");
    }
    types.sort();
    if (types[0] == types[1] && types[1] == types[2] && types[2] == types[3] && types[3] == types[4] && types[4] == "BAN") plus = 50;
    else if (types[0] == types[1] && types[1] == types[2] && types[2] == types[3] && types[3] == types[4] && types[4] == "BELL") plus = 70;
    else if (types[0] == types[1] && types[1] == types[2] && types[2] == types[3] && types[3] == types[4] && types[4] == "CHER") plus = 90;
    else if (types[0] == types[1] && types[1] == types[2] && types[2] == types[3] && types[3] == types[4] && types[4] == "JOK") plus = 110;
    else if (types[0] == types[1] && types[1] == types[2] && types[2] == types[3] && types[3] == types[4] && types[4] == "BAG") plus = 130;
    else if (types[0] == types[1] && types[1] == types[2] && types[2] == types[3] && types[3] == types[4] && types[4] == "ORG") plus = 150;
    else if (types[0] == types[1] && types[1] == types[2] && types[2] == types[3] && types[3] == types[4] && types[4] == "CRD") plus = 170;
    else if (types[0] == types[1] && types[1] == types[2] && types[2] == types[3] && types[3] == types[4] && types[4] == "RCT") plus = 250;
    else if ((types[0] == types[1] == types[2] == types[3]) || (types[1] == types[2] == types[3] == types[4])) plus = 4 * getValue(types[1]) * getValue(types[1]);
    else if ((types[0] == types[1] && types[1] == types[2]) && (types[3] == types[4])) plus = 3 * (getValue(types[0]) + 1) + 2 * getValue(types[3]);
    else if ((types[0] == types[1]) && (types[2] == types[3] && types[3] == types[4])) plus = 3 * (getValue(types[4]) + 1) + 2 * getValue(types[0]);
    else if ((types[0] == types[1]) && (types[2] == types[3])) plus = 2 * getValue(types[0]) + 2 * getValue(types[2]);
    else if ((types[0] == types[1]) && (types[3] == types[4])) plus = 2 * getValue(types[0]) + 2 * getValue(types[3]);
    else if ((types[1] == types[2]) && (types[3] == types[4])) plus = 2 * getValue(types[1]) + 2 * getValue(types[3]);
    else if ((types[0] == types[1]) || (types[1] == types[2])) plus = 2 * getValue(types[1]);
    else if ((types[2] == types[3]) || (types[3] == types[4])) plus = 2 * getValue(types[3]);
    addPts(plus);
}
function addPts(plus) {
    pts += plus;
    const spanEl = document.getElementById("bal");
    spanEl.innerText = pts;
}
butStr.addEventListener("click", () => {
    if (!flag) {
        flag = true;
        if (pts < 20) {
            alert("Not enough pts on your account to play!");
            flag = false;
        }
        else {
            addPts(-20);
            let timerId1 = setInterval(() => roll(document.getElementById("im1")), 200);
            setTimeout(() => { clearInterval(timerId1); }, 2500);
            let timerId2 = setInterval(() => roll(document.getElementById("im2")), 200);
            setTimeout(() => { clearInterval(timerId2); }, 3100);
            let timerId3 = setInterval(() => roll(document.getElementById("im3")), 200);
            setTimeout(() => { clearInterval(timerId3); }, 3700);
            let timerId4 = setInterval(() => roll(document.getElementById("im4")), 200);
            setTimeout(() => { clearInterval(timerId4); }, 4300);
            let timerId5 = setInterval(() => roll(document.getElementById("im5")), 200);
            setTimeout(() => { clearInterval(timerId5); }, 4800);
            setTimeout(() => { countPts(); flag = false; }, 5100);
        }
    }
});



