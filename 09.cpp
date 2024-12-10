#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <optional>
#include <set>
#include <sstream>
#include <tuple>
#include <variant>
#include <vector>

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>

#define ASSERT_EQ(a, b)                                                        \
  do {                                                                         \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    if (_a != _b) {                                                            \
      std::cout << _a << " != " << _b << std::endl;                            \
      assert(0);                                                               \
    }                                                                          \
  } while (0)

#define myprint(arg)                                                           \
  do {                                                                         \
    std::cout << "" #arg << " = " << arg << std::endl;                         \
  } while (0)

using ll = int64_t;

namespace {

const std::string_view input_real =
    "98833567337520696566611819497797606683369478796723346314984920122792485648"
    "15678743918257448799319394268097164282313431712170232427711341278448916123"
    "55539896325864919225495442865312404862749036365444509846374670526457743433"
    "18727390132232578526863253966971667856388261297552452351907093995987386593"
    "44508060635161185663324868573885182433469142265019784585737647295954667470"
    "63235655231032498697858244237394668332432496497571441144203230436857121097"
    "80404523755544377232416269805940467531166565635090335822174999749910501346"
    "12298676291437298830232670458958219114171954451027352367739620478811495628"
    "75638654145471373736635611139622653164779677815644721355726410312584119171"
    "38437578793018255055334534124769288917777913517373612718246192555779755865"
    "34476383753744919060501896538114501577965998706141772971209530162029611212"
    "39433050636655476055598514248661505986366568703821417969949730151867123522"
    "50394922521528317166762492764597158738783840734640721071301150173978613398"
    "39974612262240665898961586771878531734607833716543388957148829186678512928"
    "17703394609062933352973350618818649161389779574619567680948364733265645218"
    "42684531636570201420503727654963366832478118849356922011178015922698342445"
    "42309222751840604155598822227798309394498363764883786862121857736540788261"
    "47422772757341217592107591161337826958372349356416919370304810758782487450"
    "70621726623161994643489240795689802070431977477316996440267577355427268131"
    "81286644228218672046427990847221832377789165397153394375317488763889333787"
    "12321940781921516852957990873188622623926850297570648744141699735668206430"
    "59986363283071136643555648408683619784725738411648368526382623802545589982"
    "76331311259321936449351314839691926943221768453235649270701181576626894059"
    "38997449933964671073271669394472667059701421631745553615485091257021172342"
    "10847268371630666784514942988358563951771697994469846219428061263537195034"
    "76824664397994141971252455842399737184857680309555968583267395151918467779"
    "14208188501632964035873431865161481527471421736181954141124548274494272722"
    "37243410367197622950936915939436426959819042458117639314375066641690192533"
    "86477962205615978146656122809239164153984041695920788386152526156651567161"
    "52961346107594998711243468843057793130956616993865823813138874867350239319"
    "29667327276691768922309193355120427680197524904299246149955487904852369198"
    "92572581165918181889945981625991679388139740392886185070704069391458729396"
    "62906496771929415798542851274948506870315162944451582664146536379431166890"
    "74585470742874192274481542971920116036643092924161781316836447528720502580"
    "37223667895571881735267731619682303693113966616892347897586716546532647515"
    "25496920395868203222408661353485609531217339217682162748735843815592669038"
    "89941758558392482595925831581159241765811942281351443212121446124048141738"
    "18165971197080324010425577891463533490228555831854329959177368166973665428"
    "48914319349836996639703997402245911521282730276978633538371175328987885888"
    "83474777636031169597483719113588729410471691339432308739838511906960847535"
    "33987563447044225998578548836074893487135550728570221787647980451277456271"
    "89187162463888405296546822791672708786986179555588688596815947479339279552"
    "87169724743062856999401774386942655573217766906142265013495181458870364148"
    "62424271735173151666215396509958697963466163651799397415229168111121912551"
    "48957039488571534418911011236128243360412416363217535752633711845213215996"
    "31823416305396809770217538805792394570895516349940265382896635283253392363"
    "28152566952086836038905324227172132834124329594591191923629950743453145992"
    "30606467222276223580796359381769566051517248248945368891957059559143375127"
    "30301836837149954787556675933259362045849413269691972264711286827289998459"
    "78288190492744518431783416339478743290182163593658604157792595274347414386"
    "86604855343019892382833687369329585183146528704711248672534963208190533375"
    "83311199962111275662345022954182825581613125377817385841123916148565162958"
    "72955898538881702494502275922438131954803275957973305149586967106220974672"
    "72401836119218611890612816317662667487324487451843143696684021817872429614"
    "20546423325574181291324149561232144071584196795962791813417454958130392351"
    "43194037441769115217676181107224378686288044659623815988405093577141274491"
    "49427028454618458374787321405342332445884631446228286239247231808433606053"
    "17381518294850762957821130405013654773645241665056603168659523266096617981"
    "43592651341054228799358817759077687559318451287829184584385093763848924720"
    "11443761542790485216652258645354918917851369166996306220237776771386608496"
    "91385812216446423883995155725327174381592634325832935597545496692965787589"
    "84347086627546465729605425905342101995416573335592158918466882541643249199"
    "90169746735347225017585247993879141429516543314479669147848647125130152643"
    "92967444575364793514132547519132622928104018511770402869599292526859794621"
    "73928453424181742375153072621370196987618980939081678477621248512397161496"
    "56137479788637188513469139818520441386334884613358952013417668144578739978"
    "60958189336643841834275827284614163728113648968751868141923975371822442092"
    "97699374782329548370982283244568347180377438697436769588211147489572225869"
    "28991567873540597795561178672296283942587589614583615753214817759032367366"
    "15956757603988796749585886849417575276601312844950905871204293959167535956"
    "21718487925288324276511897387259894614543017155269757980165877386816289598"
    "58112974155382692127981584999760129547731821767163388645958319979266465279"
    "22375535572988799111917266649575226282804885596093316731614712154912616560"
    "77833025156243223613651267812936647915922771602291878249426456657170877766"
    "65244011972579813723669744624362374795209219829849129371755134406089915993"
    "43567547132872339887755979134078338328215177102079728961546377739497525496"
    "52316350784061433763175887354294973443432075491063295635718679865271717197"
    "69275121689846646497772737303573533761964231589722828677804693597267629115"
    "70947926374863673446979261643626721188401262342220221678104748284042597016"
    "35339838619688621165477773519813975974119050657962471951967662135826361927"
    "67436591293254421032788339476474269349249835863979791379316567522026326776"
    "45151878965941669883983231449888443323104092764483978884113141858820195383"
    "59434410898991975023609032111767196983746852191727117694312525529312979422"
    "56398359666723124473569622776823182339425470636786142799991584157487173950"
    "29584950249214823752643477251174183692504374637933297852249059926844949769"
    "94345413663252629190526169492437863027811827395072638493319834411679973598"
    "83392691763531823084754992648698455557593626516124908367995777587845643024"
    "48857811895278105867673715702687333396149163254924987228614621451445851720"
    "83785627558451569647242372647113602570963095195526251747743377484637208429"
    "16939184179157657782154878474384704560384825357339672698601048848572451129"
    "63177791489532791245727349615251446637885410318294393284857642363895247257"
    "50574924955224512159226810741863167669289751303648851248799554104765601536"
    "17982187241991643350693655519353666170663468803929591546183696876916399434"
    "11186396409197954041479334845839992552628351305096101152939190948023345316"
    "36491840487441956648269753906091548766333284886769567419576499547484957039"
    "10305214148166712559667119461726417610297039217920133756477091221094301520"
    "33575494278948225168807571258550174816901431938597696989237593153538602054"
    "77764052446110158873208167146159773031609545598613924922403957894319914486"
    "21427628537326793132651792579671344011953095968146542250243112478740721071"
    "90166012894730119369606344358654727284125940383143773716299893254512605970"
    "40987079419244216625219042928049436462823767396545627662384468208636911356"
    "93541286648868222310509870435191768646231746273749507825953381972456319614"
    "27403838708389703988248972186245631539182434442889329862995838794347778727"
    "28797391951096517361157031975220487824964765206833417591584320413070957565"
    "46275086946811806873988735335617325188387956499178233498323999467567118796"
    "46483487463649779329415780981064975182745936299987394528672337243016172477"
    "47461181675033569757405914624084617431304688551663802455601699952448718537"
    "22702864239464784587503016287347415578757038923250211183305378675839719744"
    "49122857159316414528664590161355714384209055961823188517435139732748856439"
    "88767539699913422282465984693031233445641547432292324497816881584881921455"
    "40754698354398274491422321148155171338859016544346714383621370411693664491"
    "32343027324194767145366534925416501935385837666759804112252583889044698083"
    "33548776389373554798162057953994187749792157721191417115879418923652566924"
    "32217511337012329124886613193472803087112927375632313845452674439771447716"
    "46626781702667672077381417373224444572628188899186577230472773366393114226"
    "61292245415664665679939720685089986275972755469876619265807572869691812540"
    "14311694618830577252545198431652914294384773976936408966827853234147266889"
    "99645486718016775476552845246915228458639076613324254730487962915290601046"
    "46943543242644785993667484604322619926714135363664242234797818669825284349"
    "64106734883463882593797653116470299365475526702646802828232215131832338354"
    "49128917995849274193997112579328205240195116489831477073194162121387619831"
    "79614075947884513751587480556343267138511220492730932194903095129997865667"
    "75202589617816877831276967697331374194636415828466367671258112619159474945"
    "66963569439829857197927181202830716348946397828763849426191866292855142446"
    "46446276811559585938784996513539217080497590264040595468899471826313528045"
    "22231197365913622416847447707326371071431240151629875278372373313257629437"
    "51489175498016872477257860969539106356121584232640263647674016296729771428"
    "24675884437978818877532650467813881335887184169897801949479139561121557374"
    "71426811231219967469337838312355184112415252563583148376908420128522298852"
    "92255264277248205126119767177570326163304752696842988023327215181723826432"
    "61568798115759763674218539933065288769882029276526988932997439668829252573"
    "17769831129414998377505012949497133215583422954261438461436378929958246861"
    "94817947535388782370788220931774802296168936507396181865604778534940158081"
    "90999386187221112835682661778530254353528145929646747070418588992874869834"
    "33674778416080363911986990843470828681673791941693676648436578996168958120"
    "26671784128414182379219743359318341623819244955325713032861350477816905314"
    "25403085662520734974325720961919706653973438432277444132257635723236242481"
    "57173615761472161993791294623570837067728468428728686291774288105598832731"
    "14573015467782448511287245685335375941385371786392973538807056376128858771"
    "36336013214118283975679792134536326662228548882487671665508189766433747463"
    "79553345263925946539135818169758706527913818431460295937185462167583843583"
    "22583364962376177799937356674182341761469364362591689473966829998949556590"
    "55817127357567593394797375162816495112742211472421417542734461604328877268"
    "34713267752883336510139954917710598664544911999656133857698373276136781318"
    "52753358612925942674415165469788858687315371956494588965245461246932681622"
    "48306493697839383363454521958915751930925213217627713472521830363388882813"
    "98133329337847963365193198459592318392992270283496684428545646944510512689"
    "68543686969462546683816417883059864622408353932297839990801564307169301814"
    "57195935656397784952542830289785909252153982533332458022803474184516234763"
    "68452170562281114567908215128735672353799935681451253252894952896957914915"
    "34202615257173367282548554578279802424273042573164378218681617263752977454"
    "26711048769060879245681159838438595564231082891597185147474329185291245193"
    "10495434126682701246611942771071636176249649727152673064324162779077866795"
    "98963450646084386628937611305128298471211454432146394122812776462442642934"
    "79869736776852446198669374601371636554711726845892357654378590208272665129"
    "16608623663671815752433781165227928384562010395148466220444413703783859371"
    "65749320318154272310566355806085462962333865985719683844414432636485475136"
    "57497758603765738354528157578318266460565644125676694848913622905317825980"
    "54222679169512378372888159209892224374193460724189238076445927274169581774"
    "73628680385771653598292870479949166619585834475437162657434910843498823096"
    "96279131416771192463894871798276256038329986927658216244841243929145518992"
    "27472193589271703775198741102212999867449898194290622282979588166783105085"
    "72541799296366978621555570812072483360128493685868463642466824685965842279"
    "18659329347194812776589361831491585814421023357676102175876363832595274114"
    "13753620957454482536221956131928493821402490374880353939267952846629982489"
    "65508044434466131882813534444688856253106382939520103469649955248610345291"
    "97984964478376694431778475374325642770609251467057219274367932833869822783"
    "51471883656350616353433854848411457635945980235488631174196062827947984117"
    "87958938455515682693995778461722791241614354893426685863493173298726743262"
    "28863962813645315423417015676112675571905611663349145153531034403010121230"
    "41352523724392656844333849535656803799987036821263142497101563925219767689"
    "62185822212716336395848638834764228010939829158559893150799814811156536565"
    "15396597144516992884707788254456898021105752159350207689797625203774248828"
    "66682417804923821154507271775614102045308693959635806715445446982748574916"
    "52182234459487391633337692416793258260495724887399785815603218654625586864"
    "12232868766211387579443898987472933063362273276621648570879416542180727314"
    "36915437794065896565153713676940191042498443447459971762812327733063259771"
    "70523285149612809876921847745291111659963767133357169150975037781967419597"
    "43976712578096663843919527843748966263645268486572487333199866647414302517"
    "18599094427518927959947610894881484447979745199485749882513930899936227797"
    "58387523738768497653534063215184937190246013989671171266756844383242147072"
    "55963551912627812726823467271440104569959638701254673847686892322659269438"
    "19129245464058991517105454177986496019687275999327299999436155893032222633"
    "92505529288780516120701049137195927697395275436643632082998450515982181593"
    "15165292706331396133576692331148869665783187473163779475127711144998841473"
    "95418471129695967099803523576374752964745618825261639751106449583262261051"
    "26224298214450163278209757559986938423621344656092708630331299615623965494"
    "35338586198563992216846142989932249969101535435684889022218510866318824367"
    "52657294479570126653125996629182633156595018982564717468283818377442794741"
    "55608168116120503527372639731052818123899214227110871641825686703171656467"
    "14182440661055381478247181808580511746476874721445762976444141977588173328"
    "24213122714748804310235180669867228066312817435233651493859930513188969314"
    "23361290668136114344247024672473625930133865593538219715896790978115754973"
    "99196911143992496274655978715883136585606930437668166225566586741178663830"
    "33774866612065431334556413188835194275192981335261656858353165646016136026"
    "22879890559234491157233143126385986443473578521012296382112952358261994195"
    "29564072255776988278266041606510364484421272474269671333233171755916647444"
    "61705779277736275845649382311469101991682379456369322456796569977240473849"
    "88928925579873497530455071898627565134799630849184338460432977737135521847"
    "35178444528529507922847850182748671835105892964058384824129948415690909067"
    "46925280211228994074702010704261891397569411386184129631544899833872977070"
    "60751764476446723726429559634070278665316113429599682813566726969242936682"
    "35378697525664912724784027164858201094527579287624679181197234361482684077"
    "87127672878815943569935056424670117726785368542136647941897738486780295580"
    "30676230184210435967412953951173814545231864226154303981962428252181397564"
    "98107776299919923990277614317514254319647176164774539059469459273156184687"
    "13488673228934725932308246195997315536457655304115795244362942239479612059"
    "48883854965451777758757563258619262142911850634812948749287314227995982854"
    "82459849358195636148579116417121745476449279823242866066102823274343994631"
    "23302991399747263696384716505365369610532518153138175076913364595635436572"
    "29822197346513401881746733279443318934274968104915894272702896394026462267"
    "11287010197277345173318251507755146643547630528289954530503112342780875519"
    "31276013814161932249632465726442863030355226936953414855714429874322478645"
    "92853224726736819431255549859481638425751296822366611276553460545893938176"
    "58386596419268328656257467429815453879409578518592706815886573863879378611"
    "70278246823040802997802819385813749878155079889733739061583945719939742811"
    "14137227777636761283646063349093744396766736728535317264176169878671879147"
    "22739850898627299196541262145670152016219190857499211168453797692977572959"
    "28159792939782296247771761598439627416493950602277675494134118216074896996"
    "87675986171695816623977714286168991869156964953386794510359997578343703549"
    "24879113741549942795772923668558947377915787314396371394784574968656158657"
    "56503469332745666917754291505190557547605978322054593823451166439688236013"
    "92861750462982174367607664784441442390157418698460295921984866309519935570"
    "29614379476451855626704420128482327451306211791445514343485438834838254817"
    "52856746189542443492773759695331598730104186424618807662409988222513898597"
    "40703150968952473715943155189412997353681956639762558763115361178776716967"
    "13896571239689407411105863756557126785316795308321935041688243204793646782"
    "43284289661532824041117815238083631079842144141499855066272113336770769562"
    "47108960793569969933988634267319313671362788551442599583741235882190983013"
    "13434052176087104260814545475984715232614135281064485520635647985723917549"
    "69854763516171415694649160489513258317591593698632174778478215932783221626"
    "23635123144630478320258136508665804614262397869194108926383549862483121860"
    "78607613292361444941481225631938207179352183101491743583202525718936755176"
    "27374547651479741967938541365258378969554445257448891093141980309438297233"
    "16621559342375196630358244621390569692935962233867402713962446488126262086"
    "85795151783198808765533716762215903286314824679789706966919730981389129868"
    "22326450914991832623135494977559289477306094772123177156752079509343594329"
    "89355311271560361532295278931581936925473941579853448927785763961658539414"
    "33272563854629232415414558109468168580524017852887924867859193824113874799"
    "83617579564235218950609374777162228679591332178183521424703949416714302492"
    "61107859639952431681201241511751175275855147884230233435483370534895584542"
    "52283119447817657214985891662945789263812772977599415677761196381630436217"
    "54265918977489547390506831281011479540411575297180789237294438503954276559"
    "93201720623939196756938631782042857381963116644321314371988958951670796424"
    "38744971794673623472384321327130295244905287363349231569734748752634443433"
    "86299171862412329349379575348235295887688818672982783413691049752111322938"
    "23782647244650374988177959443019715549266398843449178643529128508151823735"
    "19382370193416377770789013827445711290637077463235494549834253518858208063"
    "20883732402896865039809329341523825020958447667081327057733323644744947691"
    "58416577254036405134409898484440962611466040931778658568676128675543486427"
    "27386495831786896854473143839375792289368695951677651330795881722354919165"
    "98574436464549558838763576551258533699494094705040356491257364416212926115"
    "88632266979591801858532252859489334736944293416228451089109860579581862282"
    "83388596609389382957848980671524959892333379899910785149696732686117329513"
    "64425264498169176931395156203742122299332751147594632033751833243435651171"
    "22599191606841681297316255197097191085155838462263579918326629636544271333"
    "59517239771987149692949560235952873845479365716649255485336458641678652557"
    "83241895836427377345455892184067929128209740146179462979276989882122469417"
    "17893183711856345816645757902119143036808063469533555770351369653735303490"
    "83216614907713955965674163396666802591993767767387548959681183517692702051"
    "75169027994837154668978627571795369283963086925393964373964463208173783963"
    "63929691408198703646118933548111712773418977729426853075413789787255252755"
    "44286263658370642730212142991677979888586318155787998298197290786627724729"
    "87112712922664907736952221491559191561328442223496823793271868549653914029"
    "76927977286561735770275415733186319058899139202781689652925039974961388472"
    "65404592246221721197612058875021818240531368656885324733776159855470235250"
    "43966749533150525196438196279064471321641495406745172423217799131128543725"
    "55758539519240227697565685577598889347842894317668101657987751247523487697"
    "64812653485034652388885945266761959047895756407468418363815018837670378564"
    "59527185618417669489529341784698954481291535834427147880388034416756482191"
    "8594453538344091329";
const std::string_view input_test = "2333133121414131402";
// auto &input = input_test;
auto &input = input_real;

struct DataSequence {
  ll _index = 0;
  ll _id = 0;
  ll _space_size = 0;
  ll _data_size = 0;
};

struct EmptySequence {
  ll _index = 0;
  std::vector<ll> _data;
  ll _empty_size = 0;
};

using DiskEntry = std::variant<DataSequence, EmptySequence>;

std::vector<DiskEntry> disk;
std::list<EmptySequence *> empty_sequences;

void init_disk() {
  disk.clear();
  empty_sequences.clear();
}

void build_disk() {
  disk = std::vector<DiskEntry>(input.size());
  ll id = 0;
  for (ll i = 0; i < disk.size(); i++) {
    assert(isdigit(input.at(i)));
    ll nr = input.at(i) - '0';
    if (i % 2 == 0) {
      disk.at(i) = DataSequence{
          ._index = i, ._id = id++, ._space_size = nr, ._data_size = nr};
    } else {
      disk.at(i) = EmptySequence{._index = i, ._data = {}, ._empty_size = nr};
      empty_sequences.insert(empty_sequences.end(),
                             std::get_if<EmptySequence>(&disk.at(i)));
    }
  }
};

EmptySequence *find_next_empty(ll from_index) {
  for (auto *s : empty_sequences) {
    if (s->_index > from_index && s->_empty_size > 0) {
      return s;
    }
  }
  return nullptr;
}

void print_disk() {
  for (auto &disk_entry : disk) {
    if (auto *data_sequence = std::get_if<DataSequence>(&disk_entry)) {
      for (ll i = 0; i < data_sequence->_data_size; i++) {
        std::cout << data_sequence->_id;
      }
      for (ll i = 0;
           i < (data_sequence->_space_size - data_sequence->_data_size); i++) {
        std::cout << '.';
      }
    } else {
      auto *empty_sequence = std::get_if<EmptySequence>(&disk_entry);
      for (ll i = 0; i < empty_sequence->_data.size(); i++) {
        std::cout << empty_sequence->_data.at(i);
      }
      for (ll i = 0; i < empty_sequence->_empty_size; i++) {
        std::cout << '.';
      }
    }
  }
  std::cout << std::endl;
}

void compact() {
  for (auto it = disk.rbegin(); it != disk.rend(); it++) {
    if (auto *data_sequence = std::get_if<DataSequence>(std::addressof(*it))) {
      do {
        auto *empty_sequence = find_next_empty(0);
        if (!empty_sequence || empty_sequence->_index > data_sequence->_index) {
          return;
        }
        ll move_size =
            std::min(empty_sequence->_empty_size, data_sequence->_data_size);
        std::vector<ll> move_data(move_size, data_sequence->_id);
        data_sequence->_data_size -= move_size;
        empty_sequence->_empty_size -= move_size;

        empty_sequence->_data.insert(empty_sequence->_data.end(),
                                     move_data.begin(), move_data.end());
        if (data_sequence->_data_size == 0) {
          break;
        }
      } while (true);
    }
  }
}

void compact2() {
  for (auto it = disk.rbegin(); it != disk.rend(); it++) {
    if (auto *data_sequence = std::get_if<DataSequence>(std::addressof(*it))) {

      ll search_from = 0;
      do {
        auto *empty_sequence = find_next_empty(search_from);
        if (!empty_sequence || empty_sequence->_index > data_sequence->_index) {
          break;
        }
        if (empty_sequence->_empty_size >= data_sequence->_data_size) {
          auto move_size = data_sequence->_data_size;
          std::vector<ll> move_data(move_size, data_sequence->_id);
          data_sequence->_data_size -= move_size;
          empty_sequence->_empty_size -= move_size;

          empty_sequence->_data.insert(empty_sequence->_data.end(),
                                       move_data.begin(), move_data.end());
          break;
        } else {
          search_from = empty_sequence->_index;
        }
      } while (true);
    }
  }
}

ll checksum() {
  ll sum = 0;
  ll position = 0;
  for (auto &disk_entry : disk) {
    if (auto *data_sequence = std::get_if<DataSequence>(&disk_entry)) {
      for (ll i = 0; i < data_sequence->_data_size; i++, position++) {
        sum += data_sequence->_id * position;
      }
      for (ll i = 0;
           i < (data_sequence->_space_size - data_sequence->_data_size);
           i++, position++) {
      }
    } else {
      auto *empty_sequence = std::get_if<EmptySequence>(&disk_entry);
      for (ll i = 0; i < empty_sequence->_data.size(); i++, position++) {
        sum += empty_sequence->_data.at(i) * position;
      }
      for (ll i = 0; i < empty_sequence->_empty_size; i++, position++) {
      }
    }
  }
  return sum;
}
} // namespace

int main09() {
  int64_t result0 = 0;
  int64_t result1 = 0;

  init_disk();
  build_disk();
  compact();
  result0 = checksum();

  init_disk();
  build_disk();
  compact2();
  result1 = checksum();

  myprint(result0);
  myprint(result1);
  return 0;
}
