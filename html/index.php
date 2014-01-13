<?php

	if($_GET['v'] && strlen($_GET['v']) >= 3)
	{
		$version = str_replace('.', '-', $_GET['v']);
		$filename = dirname(__FILE__) . '/' . $version . '.php';
		
		if(file_exists($filename))
		{
			require($filename);
		} else {
			echo '<h1>Error</h1><p>Unable to locate configuration page for this version.</p><p>Please contact an <a href="mailto:me@mattcongrove.com">administrator</a>.</p>';
		}
	} else {
		echo '<h1>Error</h1><p>Unable to locate configuration page for this version.</p><p>Please contact an <a href="mailto:me@mattcongrove.com">administrator</a>.</p>';
	}

?>