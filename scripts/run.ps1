param(
    [int]$Workload,
    [switch]$All
)

if ($PSBoundParameters.Count -eq 0) {
    Write-Host "Error: Missing Parameters."
    Write-Host "Pass in the  -All or -Workload n to run."
}
else {

    if($All) {
	# Run Workload 1
	& .\bin\OS.exe conf\workload-1.txt
	
	# Run Workload 2
	& .\bin\OS.exe conf\workload-2.txt
	
	# Run Workload 3
	& .\bin\OS.exe conf\workload-3.txt
    }
    else {
	switch($Workload) {
	    1 {
		# Run Workload 1
		& .\bin\OS.exe conf\workload-1.txt
	    }
	    
	    2 {
		# Run Workload 2
		& .\bin\OS.exe conf\workload-2.txt
	    }
	    
	    3 {
		# Run Workload 3
		& .\bin\OS.exe conf\workload-3.txt
	    }
	    
	    default {
		Write-Host "Invalid Workload ID"
	    }
	}
    }

}
