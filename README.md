# DominantPointDetection

To install the program see <a href="https://github.com/ngophuc/DominantPointDetection/blob/master/INSTALL.txt">INSTALL.txt</a> file


If you want you can also directly test the programm online:

http://ipol-geometry.loria.fr/~phuc/ipol_demo/ATC_IPOLDemo/


* [![Build Status](https://travis-ci.org/ngophuc/DominantPointDetection.svg?branch=master)](https://travis-ci.org/ngophuc/DominantPointDetection)

# Examples

<p>File <a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/pentagonNoise4.sdp">pentagonNoise4.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATC_Computation -i ../Samples/pentagonNoise4.sdp -o ../Results/pentagonNoise4 -d ../ImaGene-forIPOL &#x000A;--maxScale 10 --samplingStep 1.0</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/pentagonNoise4.png">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/pentagonNoise4.png" alt="Input image" />
			</a>	
		<br />
		Input image
		</td>		
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/pentagonNoise4.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/pentagonNoise4.png" alt="Input curve" />
			</a>	
		<br />
		Input curve
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/pentagonNoise4DP.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/pentagonNoise4DP.png" alt="DP result" />
			</a>
		<br />
		Dominant points (without optimisation)
		</td>
    <td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/pentagonNoise4newDP.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/pentagonNoise4newDP.png" alt="DP result" />
			</a>
		<br />
		Dominant points (with optimisation)
		</td>  
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/circle50.sdp">circle50.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATC_Computation -i ../Samples/circle50.sdp -o ../Results/circle50 -d ../ImaGene-forIPOL &#x000A;--maxScale 10 --samplingStep 1.0</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/circle50.png">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/circle50.png" alt="Input image" />
			</a>	
		<br />
		Input image
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/circle50.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/circle50.png" alt="Input curve" />
			</a>	
		<br />
		Input curve
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/circle50DP.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/circle50DP.png" alt="DP result" />
			</a>
		<br />
		Dominant points (without optimisation)
		</td>
    <td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/circle50newDP.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/circle50newDP.png" alt="DP result" />
			</a>
		<br />
		Dominant points (with optimisation)
		</td>
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/circle50Noise4.sdp">circle50Noise4.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATC_Computation -i ../Samples/circle50Noise4.sdp -o ../Results/circle50Noise4 -d ../ImaGene-forIPOL &#x000A;--maxScale 10 --samplingStep 1.0</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/circle50Noise4.png">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/circle50Noise4.png" alt="Input image" />
			</a>	
		<br />
		Input image
		</td>		
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/circle50Noise4.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/circle50Noise4.png" alt="Input curve" />
			</a>	
		<br />
		Input curve
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/circle50Noise4DP.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/circle50Noise4DP.png" alt="DP result" />
			</a>
		<br />
		Dominant points (without optimisation)
		</td>
    <td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/circle50Noise4newDP.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/circle50Noise4newDP.png" alt="DP result" />
			</a>
		<br />
		Dominant points (with optimisation)
		</td>
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/CircleRect.sdp">CircleRect.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATC_Computation -i ../Samples/CircleRect.sdp -o ../Results/CircleRect -d ../ImaGene-forIPOL &#x000A;--maxScale 10 --samplingStep 1.0</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/CircleRect.png">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/CircleRect.png" alt="Input image" />
			</a>	
		<br />
		Input image
		</td>			
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/CircleRect.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/CircleRect.png" alt="Input curve" />
			</a>	
		<br />
		Input curve
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/CircleRectDP.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/CircleRectDP.png" alt="DP result" />
			</a>
		<br />
		Dominant points (without optimisation)
		</td>
    <td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/CircleRectnewDP.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/CircleRectnewDP.png" alt="DP result" />
			</a>
		<br />
		Dominant points (with optimisation)
		</td>
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/flower100Noise4.sdp">flower100Noise4.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATC_Computation -i ../Samples/flower100Noise4.sdp -o ../Results/flower100Noise4 -d ../ImaGene-forIPOL &#x000A;--maxScale 10 --samplingStep 1.0</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/flower100Noise4.png">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Samples/flower100Noise4.png" alt="Input image" />
			</a>	
		<br />
		Input image
		</td>			
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/flower100Noise4.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/flower100Noise4.png" alt="Input curve" />
			</a>	
		<br />
		Input curve
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/flower100Noise4DP.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/flower100Noise4DP.png" alt="DP result" />
			</a>
		<br />
		Dominant points (without optimisation)
		</td>
    <td align="center" valign="center">
			<a href="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/flower100Noise4newDP.pdf">
				<img width="150" src="https://github.com/ngophuc/DominantPointDetection/blob/master/Results/flower100Noise4newDP.png" alt="DP result" />
			</a>
		<br />
		Dominant points (with optimisation)
		</td>
		</tr>
	</table>
</p>
