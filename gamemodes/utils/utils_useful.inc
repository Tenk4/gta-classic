Date_Get() {
    new 
        date[11], 
        month, 
        day, 
        year;

    getdate(year, month, day);
    format(date, sizeof(date), "%02d/%02d/%04d", day, month, year);

    return date;
}

Time_Get() {
    new 
        time[9], 
        hour, 
        minute, 
        second
    ;

    gettime(hour, minute, second);
    format(time, sizeof(time), "%02d:%02d:%02d", hour, minute, second);

    return time;
}

ClearPlayerChat(playerid, lines) {
    for(new i = 0; i <= lines; i++)
    {
        SendClientMessage(playerid, COLOR_WHITE, "");
    }
    return 1;
}