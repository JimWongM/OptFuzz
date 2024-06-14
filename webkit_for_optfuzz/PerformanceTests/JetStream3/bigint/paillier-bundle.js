// MIT License

// Copyright (c) 2018 Juan Hernández Serrano

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

var paillierBigint=function(n){"use strict";function t(n){return n>=0?n:-n}function e(n){if("number"==typeof n&&(n=BigInt(n)),1n===n)return 1;let t=1;do{t++}while((n>>=1n)>1n);return t}function r(n,t){if("number"==typeof n&&(n=BigInt(n)),"number"==typeof t&&(t=BigInt(t)),n<=0n||t<=0n)throw new RangeError("a and b MUST be > 0");let e=0n,r=1n,i=1n,o=0n;for(;0n!==n;){const s=t/n,u=t%n,a=e-i*s,c=r-o*s;t=n,n=u,e=i,r=o,i=a,o=c}return{g:t,x:e,y:r}}function i(n,e){let r="number"==typeof n?BigInt(t(n)):t(n),i="number"==typeof e?BigInt(t(e)):t(e);if(0n===r)return i;if(0n===i)return r;let o=0n;for(;0n===(1n&(r|i));)r>>=1n,i>>=1n,o++;for(;0n===(1n&r);)r>>=1n;do{for(;0n===(1n&i);)i>>=1n;if(r>i){const n=r;r=i,i=n}i-=r}while(0n!==i);return r<<o}function o(n,e){return"number"==typeof n&&(n=BigInt(n)),"number"==typeof e&&(e=BigInt(e)),0n===n&&0n===e?BigInt(0):t(n/i(n,e)*e)}function s(n,t){if("number"==typeof n&&(n=BigInt(n)),"number"==typeof t&&(t=BigInt(t)),t<=0n)throw new RangeError("n must be > 0");const e=n%t;return e<0n?e+t:e}function u(n,t){const e=r(s(n,t),t);if(1n!==e.g)throw new RangeError(`${n.toString()} does not have inverse modulo ${t.toString()}`);return s(e.x,t)}function a(n,e,r){if("number"==typeof n&&(n=BigInt(n)),"number"==typeof e&&(e=BigInt(e)),"number"==typeof r&&(r=BigInt(r)),r<=0n)throw new RangeError("n must be > 0");if(1n===r)return 0n;if(n=s(n,r),e<0n)return u(a(n,t(e),r),r);let i=1n;for(;e>0;)e%2n===1n&&(i=i*n%r),e/=2n,n=n**2n%r;return i}function c(n){let t=0n;for(const e of n.values()){t=(t<<8n)+BigInt(e)}return t}function f(n,t=!1){if(n<1)throw new RangeError("byteLength MUST be > 0");{const e=new Uint8Array(n);return self.crypto.getRandomValues(e),t&&(e[0]=128|e[0]),e}}function h(n,t=!1){if(n<1)throw new RangeError("bitLength MUST be > 0");const e=Math.ceil(n/8),r=n%8;return new Promise(((n,i)=>{(function(n,t=!1){if(n<1)throw new RangeError("byteLength MUST be > 0");return new Promise((function(e,r){{const r=new Uint8Array(n);self.crypto.getRandomValues(r),t&&(r[0]=128|r[0]),e(r)}}))})(e,!1).then((function(e){if(0!==r&&(e[0]=e[0]&2**r-1),t){const n=0!==r?2**(r-1):128;e[0]=e[0]|n}n(e)}))}))}function g(n,t=!1){if(n<1)throw new RangeError("bitLength MUST be > 0");const e=f(Math.ceil(n/8),!1),r=n%8;if(0!==r&&(e[0]=e[0]&2**r-1),t){const n=0!==r?2**(r-1):128;e[0]=e[0]|n}return e}function l(n,t=1n){if(n<=t)throw new RangeError("Arguments MUST be: max > min");const r=n-t,i=e(r);let o;do{o=c(g(i))}while(o>r);return o+t}let m=!1;function d(n,t=16,e=!1){if("number"==typeof n&&(n=BigInt(n)),n<0n)throw RangeError("w MUST be >= 0");return new Promise(((e,r)=>{const i=new Worker(y());i.onmessage=n=>{i.terminate(),e(n.data.isPrime)},i.onmessageerror=n=>{r(n)};const o={rnd:n,iterations:t,id:0};i.postMessage(o)}))}function w(n,t){if(2n===n)return!0;if(0n===(1n&n)||1n===n)return!1;const e=[3n,5n,7n,11n,13n,17n,19n,23n,29n,31n,37n,41n,43n,47n,53n,59n,61n,67n,71n,73n,79n,83n,89n,97n,101n,103n,107n,109n,113n,127n,131n,137n,139n,149n,151n,157n,163n,167n,173n,179n,181n,191n,193n,197n,199n,211n,223n,227n,229n,233n,239n,241n,251n,257n,263n,269n,271n,277n,281n,283n,293n,307n,311n,313n,317n,331n,337n,347n,349n,353n,359n,367n,373n,379n,383n,389n,397n,401n,409n,419n,421n,431n,433n,439n,443n,449n,457n,461n,463n,467n,479n,487n,491n,499n,503n,509n,521n,523n,541n,547n,557n,563n,569n,571n,577n,587n,593n,599n,601n,607n,613n,617n,619n,631n,641n,643n,647n,653n,659n,661n,673n,677n,683n,691n,701n,709n,719n,727n,733n,739n,743n,751n,757n,761n,769n,773n,787n,797n,809n,811n,821n,823n,827n,829n,839n,853n,857n,859n,863n,877n,881n,883n,887n,907n,911n,919n,929n,937n,941n,947n,953n,967n,971n,977n,983n,991n,997n,1009n,1013n,1019n,1021n,1031n,1033n,1039n,1049n,1051n,1061n,1063n,1069n,1087n,1091n,1093n,1097n,1103n,1109n,1117n,1123n,1129n,1151n,1153n,1163n,1171n,1181n,1187n,1193n,1201n,1213n,1217n,1223n,1229n,1231n,1237n,1249n,1259n,1277n,1279n,1283n,1289n,1291n,1297n,1301n,1303n,1307n,1319n,1321n,1327n,1361n,1367n,1373n,1381n,1399n,1409n,1423n,1427n,1429n,1433n,1439n,1447n,1451n,1453n,1459n,1471n,1481n,1483n,1487n,1489n,1493n,1499n,1511n,1523n,1531n,1543n,1549n,1553n,1559n,1567n,1571n,1579n,1583n,1597n];for(let t=0;t<e.length&&e[t]<=n;t++){const r=e[t];if(n===r)return!0;if(n%r===0n)return!1}let r=0n;const i=n-1n;let o=i;for(;o%2n===0n;)o/=2n,++r;const s=i/2n**r;do{let t=a(l(i,2n),s,n);if(1n===t||t===i)continue;let e=1;for(;e<r&&(t=a(t,2n,n),t!==i);){if(1n===t)return!1;e++}if(t!==i)return!1}while(0!=--t);return!0}function y(){let n=`'use strict';const ${r.name}=${r.toString()};const ${u.name}=${u.toString()};const ${a.name}=${a.toString()};const ${s.name}=${s.toString()};const ${g.name}=${g.toString()};const ${f.name}=${f.toString()};const ${l.name}=${l.toString()};const ${d.name}=${w.toString()};${e.toString()};${c.toString()};`;return n+=`onmessage=async function(_e){const _m={isPrime:await ${d.name}(_e.data.rnd,_e.data.iterations),value:_e.data.rnd,id:_e.data.id};postMessage(_m);}`,function(n){n=`(() => {${n}})()`;const t=new Blob([n],{type:"text/javascript"});return window.URL.createObjectURL(t)}(n)}function b(n,t=16){if(n<1)throw new RangeError("bitLength MUST be > 0");if(!m){let e=0n;do{e=c(g(n,!0))}while(!w(e,t));return new Promise((n=>{n(e)}))}return new Promise(((e,r)=>{const i=[],o=(r,o)=>{if(r.isPrime){for(let n=0;n<i.length;n++)i[n].terminate();for(;i.length>0;)i.pop();e(r.value)}else{const e=c(g(n,!0));try{const n={rnd:e,iterations:t,id:r.id};o.postMessage(n)}catch(n){}}};{const n=y();for(let t=0;t<self.navigator.hardwareConcurrency-1;t++){const t=new Worker(n);t.onmessage=n=>o(n.data,t),i.push(t)}}for(let e=0;e<i.length;e++)h(n,!0).then((function(n){const r=c(n);i[e].postMessage({rnd:r,iterations:t,id:e})})).catch(r)}))}function p(n,t=16){if(n<1)throw new RangeError("bitLength MUST be > 0");let e=0n;do{e=c(g(n,!0))}while(!w(e,t));return e}void 0!==self.Worker&&(m=!0);class _{constructor(n,t){this.n=n,this._n2=this.n**2n,this.g=t}get bitLength(){return e(this.n)}encrypt(n,t){if(void 0===t)do{t=l(this.n)}while(1n!==i(t,this.n));return a(this.g,n,this._n2)*a(t,this.n,this._n2)%this._n2}addition(...n){return n.reduce(((n,t)=>n*t%this._n2),1n)}plaintextAddition(n,...t){return t.reduce(((n,t)=>n*a(this.g,t,this._n2)%this._n2),n)}multiply(n,t){return a(n,t,this._n2)}}class S{constructor(n,t,e,r,i){this.lambda=n,this.mu=t,this._p=r,this._q=i,this.publicKey=e}get bitLength(){return e(this.publicKey.n)}get n(){return this.publicKey.n}decrypt(n){return $(a(n,this.lambda,this.publicKey._n2),this.publicKey.n)*this.mu%this.publicKey.n}getRandomFactor(n){if(this.publicKey.g!==this.n+1n)throw RangeError("Cannot recover the random factor if publicKey.g != publicKey.n + 1. You should generate yout keys using the simple variant, e.g. generateRandomKeys(3072, true) )");if(void 0===this._p||void 0===this._q)throw Error("Cannot get random factor without knowing p and q");const t=this.decrypt(n),e=(this._p-1n)*(this._q-1n),r=u(this.n,e);return a(n*(1n-t*this.n)%this.publicKey._n2,r,this.n)}}function $(n,t){return(n-1n)/t}function R(n,t){return(l(n)*n+1n)*a(l(n),n,t)%t}return n.PrivateKey=S,n.PublicKey=_,n.generateRandomKeys=async function(n=3072,t=!1){let r,i,s,c,f,h;do{r=await b(Math.floor(n/2)+1),i=await b(Math.floor(n/2)),s=r*i}while(i===r||e(s)!==n);if(t)c=s+1n,f=(r-1n)*(i-1n),h=u(f,s);else{const n=s**2n;c=R(s,n),f=o(r-1n,i-1n),h=u($(a(c,f,n),s),s)}const g=new _(s,c);return{publicKey:g,privateKey:new S(f,h,g,r,i)}},n.generateRandomKeysSync=function(n=3072,t=!1){let r,i,s,c,f,h;do{r=p(Math.floor(n/2)+1),i=p(Math.floor(n/2)),s=r*i}while(i===r||e(s)!==n);if(t)c=s+1n,f=(r-1n)*(i-1n),h=u(f,s);else{const n=s**2n;c=R(s,n),f=o(r-1n,i-1n),h=u($(a(c,f,n),s),s)}const g=new _(s,c);return{publicKey:g,privateKey:new S(f,h,g,r,i)}},Object.defineProperty(n,"__esModule",{value:!0}),n}({});
